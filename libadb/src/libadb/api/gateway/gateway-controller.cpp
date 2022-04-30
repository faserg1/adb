#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/gateway-fsm-details.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/ready.hpp>
#include <libadb/api/gateway/data/identity.hpp>
#include <libadb/api/gateway/data/resume.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

struct GatewayController::FSMData
{
    FSM::Instance instance;
    FSMData(GatewayController *controller)
    {
        instance.setContext(controller);
    }
};

GatewayController::GatewayController(const std::string &gatewayUrl, const std::string &token, Intents requiredIntents) :
    fsm_(std::make_unique<FSMData>(this)),
    gatewayUrl_(gatewayUrl), token_(token), requiredIntents_(requiredIntents)
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
        return false;
    }
    webSocket_.connection = webSocket_.client.connect(con);
    return true;
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
    fsm_->instance.react(FSMEvent {
        .type = FSMEventType::GatewayUserRequest_Connect
    });
}

void GatewayController::stop()
{
    fsm_->instance.react(FSMEvent {
        .type = FSMEventType::GatewayUserRequest_Disconnect
    });
}

void GatewayController::runUnlessStopped()
{
    start();
    onStop_.wait();
}

Intents GatewayController::getIntents()
{
    return requiredIntents_;
}

void GatewayController::startWebSocket()
{
    webSocket_.runThread = std::jthread([this](std::stop_token token)
    {
        while (!token.stop_requested())
        {
            webSocket_.client.run();
        }
    });
}

void GatewayController::stopWebSocket()
{
    webSocket_.client.stop();
    webSocket_.runThread.request_stop();
    auto thread = std::thread([this]()
    {
        webSocket_.runThread.join();
        fsm_->instance.react(FSMEvent {
            .type = FSMEventType::ThreadWebsocketStop
        });
    });
    thread.detach();
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
    heartbeat_.lostHearbeat.store(0);
    heartbeat_.thread = std::jthread([this](std::stop_token token)
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
                fsm_->instance.react(FSMEvent {
                    .type = FSMEventType::WebSocketEventType_LostHeartbeat
                });
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(heartbeat_.interval));
        }
    });
}

void GatewayController::stopHeartbeat()
{
    heartbeat_.thread.request_stop();
    auto thread = std::thread([this]()
    {
        heartbeat_.thread.detach();
        fsm_->instance.react(FSMEvent {
            .type = FSMEventType::ThreadHeartbeatStop
        });
    });
    thread.detach();
}

void GatewayController::identity()
{
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
    sessionId_ = ready.sessionId;
}

void GatewayController::resume()
{
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

void GatewayController::scheduleUpdate()
{
    auto thread = std::thread([this]()
    {
        fsm_->instance.update();
    });
    thread.detach();
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
        fsm_->instance.react(FSMEvent
        {
            .type = FSMEventType::WebSocketEventType_Open
        });
    });
    webSocket_.client.set_fail_handler([this](auto con)
    {
        fsm_->instance.react(FSMEvent
        {
            .type = FSMEventType::WebSocketEventType_Fail
        });
    });
    webSocket_.client.set_close_handler([this](auto con)
    {
        fsm_->instance.react(FSMEvent
        {
            .type = FSMEventType::WebSocketEventType_Close
        });
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
    fsm_->instance.react(FSMEvent
    {
        .type = FSMEventType::Payload,
        .payload = &payload
    });
    handleMessage(payload);
}

void GatewayController::handleMessage(const Payload &payload)
{
    switch (payload.op)
    {
        case GatewayOpCode::HeartbeatACK:
            heartbeat_.lostHearbeat.store(0);
            break;
        case GatewayOpCode::Reconnect:
        {
            fsm_->instance.react(FSMEvent
            {
                .type = FSMEventType::GatewayRequest_Reconnect,
            });
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
    webSocket_.client.send(webSocket_.connection, jsObj.dump(), WebSocketOpcode::text, ec);
    if (ec)
    {
        auto msg = ec.message();
        return false;
    }
    return true;
}