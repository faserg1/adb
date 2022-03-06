#include <libadb/api/voice/gateway.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/voice/data/voice-server-update-event.hpp>
#include <libadb/api/voice/data/voice-state.hpp>
#include <libadb/api/voice/data/payload.hpp>
#include <libadb/api/voice/data/voice-identity.hpp>
#include <libadb/api/voice/data/hello-event.hpp>
#include <libadb/api/voice/data/ready-event.hpp>
#include <libadb/api/voice/data/ip-discovery.hpp>
#include <libadb/api/voice/data/speaking.hpp>
#include <libadb/api/voice/data/select-protocol.hpp>
#include <libadb/api/voice/data/session-description.hpp>
#include <libadb/api/user/user-api.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <stdexcept>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <iostream>

using namespace adb::api;

using WebSocketOpcode = websocketpp::frame::opcode::value;
using WebSocketError = websocketpp::lib::error_code;
namespace WebSocketCloseCode = websocketpp::close::status;
using WebSocketClientType = websocketpp::config::asio_tls_client;
using WebSocketClient = websocketpp::client<WebSocketClientType>;
using WebSocketConnection = websocketpp::connection<WebSocketClientType>;
using WebSocketConnectionPtr = std::shared_ptr<WebSocketConnection>;
using SSLContextPtr = std::shared_ptr<boost::asio::ssl::context>;

struct VoiceGateway::ConnectionData
{
    std::jthread connectionThread;
    std::jthread heartbeatThread;
    uint64_t heartbeatIntervalms = 0;
    uint64_t heartbeatNonce = 0;
    std::thread websocketThread;
    std::jthread voiceThread;
    std::unique_ptr<adb::types::Subscription> voiceStateSubscription;
    std::unique_ptr<adb::types::Subscription> voiceServerUpdateSubscription;
    VoiceState currentState;

    WebSocketClient client;
    WebSocketConnectionPtr connection;

    boost::asio::io_service ioService;
    std::unique_ptr<boost::asio::ip::udp::socket> socket;
    boost::asio::ip::udp::endpoint endpoint;

    VoiceReadyEvent readyData;
    std::string myIp;
    uint16_t myPort;
    std::string mode;
    std::vector<std::byte> secretKey;

    struct {
        std::function<std::string(const std::vector<std::string> &)> modeSelector;
        std::function<void(adb::types::SFID userId, bool)> userSpeaking;
    } callbacks;
    

    struct EventAwaits {
        std::atomic_bool voiceState = true;
        std::atomic_bool voiceServerUpdate = true;

        std::mutex mutex;
        std::condition_variable cv;

        std::promise<bool> totalConnection;
    } eventAwaits;
};


VoiceGateway::VoiceGateway(std::unique_ptr<UserApi> userApi, std::shared_ptr<Gateway> gateway, adb::types::SFID guildId) :
    gateway_(gateway), connectionData_(std::make_unique<ConnectionData>()), guildId_(guildId)
{
    if (!(gateway_->getIntents() & Intent::GuildVoiceStates))
    {
        throw std::runtime_error("Gateway should be connected with \"GuildVoiceStates\" intent!");
    }
    currentUserId_ = userApi->getCurrentUser().id;
    subscribe();
    configureClient();
    configureMessageHandler();
}

VoiceGateway::~VoiceGateway() = default;

std::future<bool> VoiceGateway::connect(adb::types::SFID channelId, bool mute, bool deaf, bool force)
{
    // если мы уже подключились или подклчаемся к какому-то каналу, мы не можем без флага force его сменить
    if ((state_ == ConnectionState::Connected || state_ == ConnectionState::Connecting) && channelId != channelId_ && !force)
        return std::async(std::launch::deferred, [](){return false;});

    if (channelId_ != channelId) {
        state_ = ConnectionState::Connecting;
    }
    
    channelId_ = channelId;

    return std::async([this, mute, deaf](){
        if (connectionData_->connectionThread.joinable()) {
            connectionData_->connectionThread.request_stop();
            connectionData_->connectionThread.join();
        }

        onPreConnect();

        connectionData_->connectionThread = std::jthread([this](std::stop_token token)
        {
            connectInternal(token);
        });

        nlohmann::json data = VoiceStateUpdate {
            .guildId = guildId_,
            .channelId = std::make_shared<adb::types::SFID>(channelId_.value()),
            .selfMute = mute,
            .selfDeaf = deaf
        };

        auto sended = gateway_->send(Payload {
            .op = GatewayOpCode::VoiceStateUpdate,
            .data = data
        });

        connectionData_->connectionThread.join();

        return state_ == ConnectionState::Connected;
    });
}

std::future<void> VoiceGateway::disconnect()
{
    nlohmann::json data = VoiceStateUpdate {
        .guildId = guildId_,
        .channelId = nullptr,
        .selfMute = connectionData_->currentState.selfMute,
        .selfDeaf = connectionData_->currentState.selfDeaf
    };

    onPreDisconnect();

    gateway_->send(Payload {
        .op = GatewayOpCode::VoiceStateUpdate,
        .data = data
    });

    return stopWebSocket();
}

void VoiceGateway::setModeSelectorCallback(std::function<std::string(const std::vector<std::string> &)> modeSelector)
{
    connectionData_->callbacks.modeSelector = modeSelector;
}

void VoiceGateway::setUserSpeakingCallback(std::function<void(adb::types::SFID userId, bool)> userSpeaking)
{
    connectionData_->callbacks.userSpeaking = userSpeaking;
}

bool VoiceGateway::send(const VoicePayload &msg)
{
    return sendInternal(msg);
}

std::future<bool> VoiceGateway::sendData(const std::byte *ptr, size_t size)
{
    using namespace boost::asio::ip;
    auto promise = std::make_shared<std::promise<bool>>();
    connectionData_->socket->async_send_to(boost::asio::buffer(ptr, size), connectionData_->endpoint,
        [promise, size](auto error, auto writedBytes)
        {
            promise->set_value(!error && writedBytes == size);
        });
    return promise->get_future();
}

std::future<size_t> VoiceGateway::receiveData(std::byte *ptr, size_t bufferSize)
{
    using namespace boost::asio::ip;
    auto promise = std::make_shared<std::promise<size_t>>();
    connectionData_->socket->async_receive_from(boost::asio::buffer(ptr, bufferSize), connectionData_->endpoint,
        [promise](auto error, auto readedBytes)
        {
            if (error)
                promise->set_value(0);
            else
                promise->set_value((size_t) readedBytes);
        });
    return promise->get_future();
}

void VoiceGateway::setBufferSize(size_t size)
{
    bufferSize_ = size;
}

std::future<std::vector<std::byte>> VoiceGateway::receiveData()
{
    return std::async(std::launch::async, [this]() -> std::vector<std::byte>
    {
        std::vector<std::byte> buffer(bufferSize_);
        auto receivedSize = receiveData(buffer.data(), buffer.size()).get();
        buffer.resize(receivedSize);
        return buffer;
    });
}

std::future<bool> VoiceGateway::sendPacket(const VoicePacket &packet)
{
    auto data = toBytes(packet);
    return sendData(data);
}

std::future<VoicePacket> VoiceGateway::receivePacket()
{
    return std::async(std::launch::async, [this]() -> VoicePacket {
        auto data = receiveData().get();
        VoicePacket packet;
        fromBytes(data, packet);
        return packet;
    });
}

void VoiceGateway::onPreConnect()
{
    connectionData_->eventAwaits.voiceServerUpdate.store(true);
    connectionData_->eventAwaits.voiceState.store(true);
}

void VoiceGateway::onPostConnect()
{

}

void VoiceGateway::onPreDisconnect()
{

}

void VoiceGateway::onPostDisconnect()
{

}

void VoiceGateway::onVoiceStateUpdated(const VoiceState &voiceState)
{
    if (voiceState.guildId != guildId_ && voiceState.channelId != channelId_)
        return;
    if (voiceState.userId == currentUserId_)
    {
        connectionData_->currentState = voiceState;
        sessionId_ = voiceState.sessionId;

        if (connectionData_->eventAwaits.voiceState.load())
        {
            connectionData_->eventAwaits.voiceState.store(false);
            connectionData_->eventAwaits.cv.notify_all();
        }
    }
}

void VoiceGateway::onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate)
{
    if (voiceServerUpdate.guildId != guildId_)
        return;
    token_ = voiceServerUpdate.token;
    if (voiceServerUpdate.endpoint)
        gatewayUrl_ = fmt::format("{}{}?v={}", "wss://", *voiceServerUpdate.endpoint, 4);

    if (connectionData_->eventAwaits.voiceServerUpdate.load())
    {
        connectionData_->eventAwaits.voiceServerUpdate.store(false);
        connectionData_->eventAwaits.cv.notify_all();
    }
}

void VoiceGateway::onMessage(const VoicePayload &payload)
{
    std::cout << fmt::format("Received OpCode: {}", (uint64_t) payload.opCode) << std::endl;

    switch (payload.opCode)
    {
        case VoiceOpCode::Hello:
        {
            auto hello = payload.data.get<VoiceHelloEvent>();
            connectionData_->heartbeatIntervalms = hello.heartbeatInterval;
            identity();
            break;
        }
        case VoiceOpCode::Ready:
        {
            startHeartbeating(connectionData_->heartbeatIntervalms);
            auto ready = payload.data.get<VoiceReadyEvent>();
            if (!startDataFlow(ready).get())
                connectionData_->eventAwaits.totalConnection.set_value(false);
            break;
        }
        case VoiceOpCode::SessionDescription:
        {
            auto desc = payload.data.get<SessionDescription>();
            connectionData_->secretKey = desc.secretKey;
            connectionData_->eventAwaits.totalConnection.set_value(true);
            break;
        }
        case VoiceOpCode::Speaking:
        {
            auto speaking = payload.data.get<SpeakingReceivePayload>();
            if (connectionData_->callbacks.userSpeaking)
                connectionData_->callbacks.userSpeaking(speaking.userId, speaking.speaking);
            break;
        }
        default:
        {
            break;
        }
    }
}

bool VoiceGateway::sendInternal(const VoicePayload &msg)
{
    nlohmann::json jsObj = msg;
    WebSocketError ec;
    connectionData_->client.send(connectionData_->connection, jsObj.dump(), WebSocketOpcode::text, ec);
    if (ec)
    {
        auto msg = ec.message();
        return false;
    }
    return true;
}

void VoiceGateway::configureClient()
{
    connectionData_->client.init_asio();
    connectionData_->client.set_tls_init_handler([](auto conHandler) -> SSLContextPtr {
        SSLContextPtr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
        return ctx;
    });
}

void VoiceGateway::configureMessageHandler()
{
    connectionData_->client.set_message_handler([this](auto conHandle, auto msg)
    {
        nlohmann::json obj = nlohmann::json::parse(msg->get_payload());
        auto payload = obj.get<adb::api::VoicePayload>();
        onMessage(payload);
    });
}

void VoiceGateway::connectInternal(std::stop_token stop)
{
    using namespace std::chrono_literals;
    std::unique_lock<std::mutex> lk(connectionData_->eventAwaits.mutex);
    while (connectionData_->eventAwaits.voiceServerUpdate.load() || connectionData_->eventAwaits.voiceState.load())
    {
        if (stop.stop_requested())
            break;
        
        connectionData_->eventAwaits.cv.wait_for(lk, 50ms, [this]() -> bool {
            return !connectionData_->eventAwaits.voiceServerUpdate.load() && !connectionData_->eventAwaits.voiceState.load();
        });
    }
    if (stop.stop_requested())
        return;
    auto futureStartWebSocket = startWebSocket();
    if (!futureStartWebSocket.get()) {
        auto futureStopWebSocket = stopWebSocket();
        return;
    }
    if (stop.stop_requested())
        return;
    if (connectionData_->eventAwaits.totalConnection.get_future().get())
    {
        state_ = ConnectionState::Connected;
    }
    else
    {
        disconnect().wait();
    }
}

void VoiceGateway::identity()
{
    auto identity = VoiceIdentity {
        .serverId = guildId_,
        .userId = currentUserId_,
        .sessionId = sessionId_,
        .token = token_
    };
    send(VoicePayload {
        .opCode = VoiceOpCode::Identify,
        .data = identity
    });
}

std::future<bool> VoiceGateway::ipDiscovery()
{
    return std::async(std::launch::async, [this]() -> bool
    {
        IPDiscovery discovery = {};
        discovery.type = IPDiscoveryType::Request;
        discovery.ssrc = connectionData_->readyData.ssrc;

        auto ipDiscoveryFutureSend = sendData(toBytes(discovery));
        if (!ipDiscoveryFutureSend.get())
            return false;

        std::vector<std::byte> discoveryData = receiveData().get();
        if (discoveryData.empty())
            return false;
        fromBytes(discoveryData, discovery);

        connectionData_->myIp = std::string(discovery.address);
        connectionData_->myPort = discovery.port;

        return true;
    });
}

void VoiceGateway::selectProtocol()
{
    if (connectionData_->callbacks.modeSelector)
        connectionData_->mode = connectionData_->callbacks.modeSelector(connectionData_->readyData.modes);
    else
        connectionData_->mode = "xsalsa20_poly1305_lite";
    SelectProtocol::SelectProtocolData protocolData = {
        .address = connectionData_->myIp,
        .port = connectionData_->myPort,
        .mode = connectionData_->mode,
    };
    nlohmann::json data = SelectProtocol {
        .protocol = "udp",
        .data = protocolData
    };
    auto payload = VoicePayload {
        .opCode = VoiceOpCode::SelectProtocol,
        .data = data
    };
    send(payload);
}

std::future<bool> VoiceGateway::startWebSocket()
{
    return std::async(std::launch::async, [this]() -> bool
    {
        WebSocketError ec;
        WebSocketConnectionPtr con = connectionData_->client.get_connection(gatewayUrl_, ec);
        if (ec)
        {
            auto msg = ec.message();
            return false;
        }
        connectionData_->client.set_close_handler([this](auto connection)
        {
            int i = 0;
        });
        connectionData_->client.set_fail_handler([this](auto connection)
        {
            int i = 0;
        });
        connectionData_->connection = connectionData_->client.connect(con);

        connectionData_->websocketThread = std::thread([this]()
        {
            connectionData_->client.run();
        });

        // heartbeat will be launched by event

        // voice will be launched by event

        return true;
    });
}

std::future<void> VoiceGateway::stopWebSocket()
{
    return std::async(std::launch::async, [this]() -> void
    {
        // stop heartbeat

        auto stopHeartbeatFuture = stopHeartbeating();
        stopHeartbeatFuture.wait();

        // stop web socket
        if (connectionData_->websocketThread.joinable())
        {
            connectionData_->client.stop();
            connectionData_->websocketThread.join();
        }

        WebSocketError ec;
        if (connectionData_->connection) {
            connectionData_->connection->close(WebSocketCloseCode::normal, "", ec);
            connectionData_->connection.reset();
        }
        state_ = ConnectionState::Disconnected;
        onPostDisconnect();
    });
}

std::future<bool> VoiceGateway::startHeartbeating(uint64_t intervalms)
{
    return std::async(std::launch::async, [this, intervalms]() -> bool
    {
        connectionData_->heartbeatThread = std::jthread([this, intervalms](std::stop_token stop)
        {
            while (!stop.stop_requested())
            {
                auto data = nlohmann::json {connectionData_->heartbeatNonce};
                sendInternal({
                    .opCode = VoiceOpCode::Heartbeat,
                    .data = data
                });
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalms));
                connectionData_->heartbeatNonce += intervalms;
            }
        });
        return true;
    });
}

std::future<void> VoiceGateway::stopHeartbeating()
{
    return std::async(std::launch::async, [this]() -> void
    {
        if (connectionData_->heartbeatThread.joinable())
        {
            connectionData_->heartbeatThread.request_stop();
            connectionData_->heartbeatThread.join();
        }
    });
}

std::future<bool> VoiceGateway::startDataFlow(const VoiceReadyEvent &voiceReady)
{
    connectionData_->readyData = voiceReady;
    return std::async(std::launch::async, [this, &voiceReady]() -> bool
    {
        using namespace boost::asio::ip;
        connectionData_->endpoint = udp::endpoint(address::from_string(voiceReady.ip), voiceReady.port);
        connectionData_->socket = std::make_unique<udp::socket>(connectionData_->ioService);
        connectionData_->socket->open(udp::v4());
        connectionData_->socket->bind(udp::endpoint(address{}, 0));

        connectionData_->voiceThread = std::jthread([this](std::stop_token stop)
        {
            while (!stop.stop_requested())
            {
                connectionData_->ioService.run();
            }
            int i = 0;
        });

        auto result = ipDiscovery().get();

        if (!result)
            return false;

        selectProtocol();

        return true;
    });
}

std::future<void> VoiceGateway::stopDataFlow()
{
    return std::async(std::launch::async, [this]() -> void
    {

    });
}

VoiceGateway::ConnectionState VoiceGateway::getState()
{
    return state_;
}

adb::types::SFID VoiceGateway::getGuildId() const
{
    return guildId_;
}

std::optional<adb::types::SFID> VoiceGateway::getChannelId() const
{
    return channelId_;
}

const VoiceState &VoiceGateway::getCurrentState() const
{
    return connectionData_->currentState;
}

const std::string &VoiceGateway::getMode()
{
    return connectionData_->mode;
}

void VoiceGateway::subscribe()
{
    connectionData_->voiceStateSubscription = gateway_->events()->subscribe<VoiceState>(Event::VOICE_STATE_UPDATE,
        [this](auto ev, auto &msg)
        {
            onVoiceStateUpdated(msg);
        });
    connectionData_->voiceServerUpdateSubscription = gateway_->events()->subscribe<VoiceServerUpdateEvent>(Event::VOICE_SERVER_UPDATE,
        [this](auto ev, auto &msg)
        {
            onServerUpdated(msg);
        });
}
