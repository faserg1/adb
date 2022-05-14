#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/gateway-fsm.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/ready.hpp>
#include <libadb/api/gateway/data/identity.hpp>
#include <libadb/api/gateway/data/resume.hpp>
#include <libadb/misc/logging.hpp>
#include <nlohmann/json.hpp>
#include <loguru/loguru.hpp>
using namespace adb::api;

struct GatewayController::FSMData
{
    std::shared_ptr<StateMachine> machine;
    FSMData(GatewayController *controller) : machine(createStateMachine(controller))
    {
    }
};

GatewayController::GatewayController(const std::string &gatewayUrl, const std::string &token, Intents requiredIntents) :
    gatewayUrl_(gatewayUrl), token_(token), requiredIntents_(requiredIntents),
    fsm_(std::make_unique<FSMData>(this))
{
    configureClient();
    configureMessageHandler();
}

GatewayController::~GatewayController() = default;

bool GatewayController::connect()
{
    WebSocketError ec;
    WebSocketConnectionPtr con = webSocket_.client.get_connection(gatewayUrl_, ec);
    if (ec)
    {
        auto msg = ec.message();
        LOG_F(ERROR, "WebSocket connection create error: {}", msg);
        return false;
    }
    webSocket_.connection = webSocket_.client.connect(con);
    LOG_F(INFO, "WebSocket connection retrived.");
    // !!!TESTCODE!!! this will try disconnect by failure
    if constexpr (false)
    {
        auto static reconnected = false;
        if (reconnected)
            return true;
        reconnected = true;
        std::thread([this]
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            webSocket_.client.close(webSocket_.connection, websocketpp::close::status::internal_endpoint_error, "Disconnecting");
        }).detach();
    }
    
    return true;
}

void GatewayController::disconnect()
{
    LOG_SCOPE_FUNCTION(INFO);
    
    if (!isWebSocketOpened() || isWebSocketStopped())
    {
        LOG_F(1, "Already disconnected");
        return;
    }
    LOG_F(INFO, "Disconnecting from gateway");
    webSocket_.client.close(webSocket_.connection, websocketpp::close::status::normal, "Disconnecting");
}

bool GatewayController::send(const Payload &msg)
{
    return sendInternal(msg);
}

void GatewayController::setDispatchFunction(DispatchCallback onDispatch)
{
    dispatchCallback_ = onDispatch;
}

void GatewayController::start()
{
    onStop_.reset();
    processEvent(fsm_->machine, StateMachineEventType::RequestConnect);
}

void GatewayController::stop()
{
    processEvent(fsm_->machine, StateMachineEventType::RequestDisconnect);
}

void GatewayController::runUnlessStopped()
{
    start();
    onStop_.wait();
    LOG_F(INFO, "runUnlessStopped done");
}

Intents GatewayController::getIntents()
{
    return requiredIntents_;
}

void GatewayController::startWebSocket()
{
    LOG_F(INFO, "Attempt to run WebSocket");
    webSocket_.client.start_perpetual();
    auto thread = std::jthread([this](std::stop_token token)
    {
        VLOG_F(vDEBUG, "WebSocket run stop requested: {}", token.stop_requested());
        while (!token.stop_requested())
        {
            webSocket_.client.run();
        }
        VLOG_F(vDEBUG, "WebSocket thread end");
        processEvent(fsm_->machine, StateMachineEventType::WebSocketStop);
    });
    webSocket_.runThread.swap(thread);
    if (thread.joinable())
    {
        thread.request_stop();
        thread.detach();
    }
}

void GatewayController::stopWebSocket()
{
    LOG_F(INFO, "Stopping WebSocket");
    webSocket_.runThread.request_stop();
    webSocket_.client.stop_perpetual();
    webSocket_.client.stop();
}

bool GatewayController::isWebSocketOpened()
{
    if (!webSocket_.connection)
        return false;
    auto state = webSocket_.connection->get_state();
    return state == decltype(state)::open;
}

bool GatewayController::isWebSocketStopped()
{
    return webSocket_.client.stopped();
}

void GatewayController::onStop()
{
    onStop_.notify();
}

void GatewayController::setHeartbeatInterval(uint64_t interval)
{
    heartbeat_.interval = interval;
}

void GatewayController::startHeartbeat()
{
    LOG_F(INFO, "Starting hearbeat");
    heartbeat_.lostHearbeat.store(0);
    auto heartbeatThread = std::jthread([this](std::stop_token token)
    {
        while (!token.stop_requested())
        {
            auto null = nlohmann::json {nullptr};
            sendInternal({
                .op = GatewayOpCode::Heartbeat,
                .data = null
            });
            heartbeat_.lostHearbeat++;
            if (heartbeat_.lostHearbeat > 3)
            {
                LOG_F(WARNING, "Heartbeat lost");
                processEvent(fsm_->machine, StateMachineEventType::LostHeartbeat);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat_.interval));
        }
        VLOG_F(vDEBUG, "Heartbeat thread end");
        processEvent(fsm_->machine, StateMachineEventType::HeartbeatStop);
    });
    heartbeat_.thread.swap(heartbeatThread);
    if (heartbeatThread.joinable())
    {
        heartbeatThread.detach();
    }
}

void GatewayController::stopHeartbeat()
{
    LOG_F(INFO, "Stopping hearbeat");
    heartbeat_.thread.request_stop();
}

void GatewayController::identity()
{
    LOG_F(INFO, "Sending identity info");
    Identity identity {
        .token = token_,
        .properties = {
            .os = "linux",
            .browser = "adb",
            .device = "adb"
        },
        .intents = requiredIntents_,
    };
    sendInternal({
        .op = GatewayOpCode::Identify,
        .data = identity
    });
}

void GatewayController::saveSessionInfo(const Ready &ready)
{
    LOG_F(INFO, "Saving session: {}", ready.sessionId);
    sessionId_ = ready.sessionId;
}

void GatewayController::resume()
{
    LOG_F(INFO, "Sending resume info");
    Resume resume {
        .token = token_,
        .sessionId = sessionId_,
        .seq = heartbeat_.sequence
    };
    sendInternal({
        .op = GatewayOpCode::Resume,
        .data = resume
    });
}

void GatewayController::configureClient()
{
    webSocket_.client.init_asio();
    webSocket_.client.set_tls_init_handler([](auto conHandler) -> SSLContextPtr {
        SSLContextPtr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
        return ctx;
    });
    webSocket_.client.set_open_handler([this](auto con)
    {
        processEvent(fsm_->machine, StateMachineEventType::WebSocketOpen);
    });
    webSocket_.client.set_fail_handler([this](auto con)
    {
        processEvent(fsm_->machine, StateMachineEventType::WebSocketFail);
    });
    webSocket_.client.set_close_handler([this](auto con)
    {
        processEvent(fsm_->machine, StateMachineEventType::WebSocketClose);
    });
}

void GatewayController::configureMessageHandler()
{
    webSocket_.client.set_message_handler([this](auto conHandle, auto msg)
    {
        nlohmann::json obj = nlohmann::json::parse(msg->get_payload());
        auto payload = obj.get<adb::api::Payload>();
        onMessage(payload);
    });
}

void GatewayController::onMessage(const Payload &payload)
{
    handleMessage(payload);
}

void GatewayController::handleMessage(const Payload &payload)
{
    VLOG_F(vDEBUG, "Gateway payload received, code: {}, event {}", static_cast<uint64_t>(payload.op), payload.eventName.value_or(""));
    processEvent(fsm_->machine, StateMachineEventType::Payload, &payload);
    switch (payload.op)
    {
        case GatewayOpCode::HeartbeatACK:
            heartbeat_.lostHearbeat.store(0);
            break;
        case GatewayOpCode::Reconnect:
        {
            processEvent(fsm_->machine, StateMachineEventType::RequestReconnect);
            break;
        }
        case GatewayOpCode::Dispatch:
        {
            if (dispatchCallback_)
                dispatchCallback_(payload);
            if (heartbeat_.sequence < payload.sequence.value_or(0))
                heartbeat_.sequence = payload.sequence.value();
            break;
        }
    }
}

bool GatewayController::sendInternal(const Payload &msg)
{
    nlohmann::json jsObj = msg;
    WebSocketError ec;
    VLOG_F(vDEBUG, "Gateway payload send, code: {}, event {}", static_cast<uint64_t>(msg.op), msg.eventName.value_or(""));
    webSocket_.client.send(webSocket_.connection, jsObj.dump(), WebSocketOpcode::text, ec);
    if (ec)
    {
        auto msg = ec.message();
        LOG_F(ERROR, "{}", msg);
        return false;
    }
    return true;
}