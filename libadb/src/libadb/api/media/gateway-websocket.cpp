#include <libadb/api/media/gateway-websocket.hpp>
#include <libadb/api/media/data/payload.hpp>
#include <libadb/api/media/data/hello-event.hpp>
#include <libadb/api/media/data/ready-event.hpp>
#include <libadb/api/media/data/voice-identity.hpp>
#include <nlohmann/json.hpp>
#include <fmt/format.h>
using namespace adb::api;

GatewayMediaWebSocket::GatewayMediaWebSocket(adb::types::SFID guildId, adb::types::SFID userId) :
    guildId_(guildId), userId_(userId)
{
    initClient();
    configureWebsocketHandlers();
}

void GatewayMediaWebSocket::setMessageHandler(MessageHandler handler)
{
    handler_ = handler;
}

bool GatewayMediaWebSocket::sendMessage(const MediaPayload &payload)
{
    return internalSendMessage(payload);
}

std::future<bool> GatewayMediaWebSocket::connect(adb::types::SFID channelId, std::string endpoint, std::string session, std::string token)
{
    channelId_ = channelId;
    gatewayUrl_ = fmt::format("{}{}/?v={}", "wss://", endpoint, gatewayWebsocketVersion_);
    sessionId_ = session;
    token_ = token;
    return internalConnect();
}

std::future<void> GatewayMediaWebSocket::disconnect()
{
    return std::async(std::launch::async, [this]() -> void {
        stopHeartbeat().wait();
        internalDisconnect().wait();
    });
}

void GatewayMediaWebSocket::initClient()
{
    client_.init_asio();
    client_.set_tls_init_handler([](auto conHandler) -> SSLContextPtr {
        SSLContextPtr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
        return ctx;
    });
}

void GatewayMediaWebSocket::configureWebsocketHandlers()
{
    client_.set_message_handler([this](auto conHandle, auto msg)
    {
        auto data = msg->get_payload();
        // Research for not documented fields
        // std::cout << "Received data: <<" << data << ">>" << std::endl;
        nlohmann::json obj = nlohmann::json::parse(data);
        auto payload = obj.get<adb::api::MediaPayload>();
        internalSendMessage(payload);
    });

    client_.set_close_handler([this](auto connection)
    {
        int i = 0;
    });
    client_.set_fail_handler([this](auto connection)
    {
        int i = 0;
    });
}

void GatewayMediaWebSocket::onHearbeatStart()
{

}

void GatewayMediaWebSocket::onHeartbeatStop()
{

}

void GatewayMediaWebSocket::onHearbeatDead()
{
    // try reconnect
}

void GatewayMediaWebSocket::internalOnMessage(const MediaPayload &payload)
{
    internalHandleMessage(payload);
    if (handler_)
        handler_(payload);
}

bool GatewayMediaWebSocket::internalSendMessage(const MediaPayload &payload)
{
    nlohmann::json jsObj = payload;
    WebSocketError ec;
    const auto data = jsObj.dump();
    client_.send(connection_, data, WebSocketOpcode::text, ec);
    if (ec)
    {
        auto msg = ec.message();
        // todo: log
        return false;
    }
    return true;
}

void GatewayMediaWebSocket::internalHandleMessage(const MediaPayload &payload)
{
    switch (payload.opCode)
    {
        case MediaOpCode::Hello:
        {
            auto hello = payload.data.get<VoiceHelloEvent>();
            heartbeatIntervalms_ = hello.heartbeatInterval;
            if (hello.version.has_value() && hello.version.value() != gatewayWebsocketVersion_)
            {
                // Disconnect and assert?
            }
            identity();
            break;
        }
        case MediaOpCode::Ready:
        {
            startHeartbeat();
            break;
        }

        case MediaOpCode::HeartbeatACK:
        {
            missedHeartBeats_.store(0);
            break;
        }
        default:
        {
            break;
        }
    }
}

std::future<bool> GatewayMediaWebSocket::internalConnect()
{
    return std::async(std::launch::deferred, [this]() -> bool
    {
        WebSocketError ec;
        WebSocketConnectionPtr con = client_.get_connection(gatewayUrl_, ec);
        if (ec)
        {
            auto msg = ec.message();
            return false;
        }
        connection_ = client_.connect(con);
        websocketThread_ = std::thread([this]()
        {
            client_.run();
        });
        return true;
    });
}

std::future<void> GatewayMediaWebSocket::internalDisconnect()
{
    client_.stop();
    return std::async(std::launch::async, [this]() -> void
    {
        websocketThread_.join();
    });
}

void GatewayMediaWebSocket::identity()
{
    auto identity = VoiceIdentity {
        .serverId = guildId_,
        .userId = userId_,
        .sessionId = sessionId_,
        .token = token_
    };
    internalSendMessage(MediaPayload {
        .opCode = MediaOpCode::Identify,
        .data = identity
    });
}

void GatewayMediaWebSocket::internalHeartBeatWorker(std::stop_token stop)
{
    onHearbeatStart();
    while (!stop.stop_requested())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(heartbeatIntervalms_));
        if (missedHeartBeats_.load() > 3)
        {
            onHearbeatDead();
            break;
        }

        auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto duration = currentTime.time_since_epoch();
        heartbeatNonce_ = duration.count();
        nlohmann::json data = heartbeatNonce_;
        internalSendMessage({
            .opCode = MediaOpCode::Heartbeat,
            .data = data
        });
        missedHeartBeats_++;
    }
    onHeartbeatStop();
}

std::future<bool> GatewayMediaWebSocket::startHeartbeat()
{
    return std::async(std::launch::deferred, [this]() -> bool
    {
        heartbeatThread_ = std::jthread([this](std::stop_token stop)
        {
            internalHeartBeatWorker(stop);
        });
        return true;
    });
}

std::future<bool> GatewayMediaWebSocket::stopHeartbeat()
{
    return std::async(std::launch::async, [this]() -> bool
    {
        if (heartbeatThread_.joinable())
        {
            heartbeatThread_.request_stop();
            heartbeatThread_.join();
        }
        return true;
    });
}