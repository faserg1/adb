#include <libadb/api/media/media-gateway.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/media/gateway-websocket.hpp>
#include <libadb/api/media/gateway-data.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/media/data/voice-server-update-event.hpp>
#include <libadb/api/media/data/voice-state.hpp>
#include <libadb/api/media/data/payload.hpp>
#include <libadb/api/media/data/voice-identity.hpp>
#include <libadb/api/media/data/hello-event.hpp>
#include <libadb/api/media/data/ready-event.hpp>
#include <libadb/api/media/data/ip-discovery.hpp>
#include <libadb/api/media/data/speaking.hpp>
#include <libadb/api/media/data/select-protocol.hpp>
#include <libadb/api/media/data/session-description.hpp>
#include <libadb/api/user/user-api.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <stdexcept>
#include <atomic>
#include <barrier>
#include <chrono>

#include <iostream>

using namespace adb::api;

struct MediaGateway::ConnectionData
{
    std::unique_ptr<GatewayMediaWebSocket> websocket;
    std::unique_ptr<GatewayMediaData> socket;

    std::unique_ptr<adb::types::Subscription> voiceStateSubscription;
    std::unique_ptr<adb::types::Subscription> voiceServerUpdateSubscription;

    std::unique_ptr<VoiceState> currentState;
    std::unique_ptr<VoiceServerUpdateEvent> currentServer;

    std::atomic_flag awaitConnectionDone;
    std::atomic_flag awaitConnectionResult;

    std::string mode;
    std::vector<std::byte> secretKey;

    struct {
        std::function<std::string(const std::vector<std::string> &)> modeSelector;
        std::function<void(adb::types::SFID userId, bool)> userSpeaking;
        std::function<void(const VoiceState &voiceState)> voiceUpdate;
    } callbacks;
};


MediaGateway::MediaGateway(std::unique_ptr<UserApi> userApi, std::shared_ptr<Gateway> gateway, adb::types::SFID guildId) :
    gateway_(gateway), connectionData_(std::make_unique<ConnectionData>()), guildId_(guildId)
{
    if (!(gateway_->getIntents() & Intent::GuildVoiceStates))
    {
        throw std::runtime_error("Gateway should be connected with \"GuildVoiceStates\" intent!");
    }
    currentUserId_ = userApi->getCurrentUser().id;
    connectionData_->websocket = std::make_unique<GatewayMediaWebSocket>(guildId, currentUserId_);
    connectionData_->socket = std::make_unique<GatewayMediaData>();
    subscribe();
}

MediaGateway::~MediaGateway() = default;

std::future<bool> MediaGateway::connect(adb::types::SFID channelId, bool mute, bool deaf, bool force)
{
    // если мы уже подключились или подклчаемся к какому-то каналу, мы не можем без флага force его сменить
    if ((state_ == ConnectionState::Connected || state_ == ConnectionState::Connecting) && channelId != channelId_ && !force)
        return std::async(std::launch::deferred, [](){return false;});

    if (channelId_ != channelId) {
        state_ = ConnectionState::Connecting;
    }
    
    channelId_ = channelId;

    return std::async([this, mute, deaf](){

        nlohmann::json data = VoiceStateUpdate {
            .guildId = guildId_,
            .channelId = std::make_shared<adb::types::SFID>(channelId_.value()),
            .selfMute = mute,
            .selfDeaf = deaf
        };

        connectionData_->awaitConnectionDone.clear();
        connectionData_->awaitConnectionResult.clear();

        auto sended = gateway_->send(Payload {
            .op = GatewayOpCode::VoiceStateUpdate,
            .data = data
        });

        while (!connectionData_->awaitConnectionDone.test())
            connectionData_->awaitConnectionDone.wait(true);

        if (!connectionData_->awaitConnectionResult.test())
        {
            disconnect().wait();
            return false;
        }

        auto ipDiscovery = connectionData_->socket->ipDiscovery().get();

        connectionData_->awaitConnectionDone.clear();
        connectionData_->awaitConnectionResult.clear();

        selectProtocol(ipDiscovery.address, ipDiscovery.port);

        while (!connectionData_->awaitConnectionDone.test())
            connectionData_->awaitConnectionDone.wait(true);

        return state_ == ConnectionState::Connected;
    });
}

std::future<void> MediaGateway::disconnect()
{
    nlohmann::json data = VoiceStateUpdate {
        .guildId = guildId_,
        .channelId = nullptr,
        .selfMute = connectionData_->currentState && connectionData_->currentState->selfMute,
        .selfDeaf = connectionData_->currentState && connectionData_->currentState->selfDeaf
    };

    gateway_->send(Payload {
        .op = GatewayOpCode::VoiceStateUpdate,
        .data = data
    });

    return connectionData_->websocket->disconnect();
}

void MediaGateway::setModeSelectorCallback(std::function<std::string(const std::vector<std::string> &)> modeSelector)
{
    connectionData_->callbacks.modeSelector = modeSelector;
}

void MediaGateway::setUserSpeakingCallback(std::function<void(adb::types::SFID userId, bool)> userSpeaking)
{
    connectionData_->callbacks.userSpeaking = userSpeaking;
}

void MediaGateway::setVoiceStateUpdateCallback(std::function<void(const VoiceState &voiceState)> callback)
{
    connectionData_->callbacks.voiceUpdate = callback;
}

bool MediaGateway::send(const MediaPayload &msg)
{
    return connectionData_->websocket->sendMessage(msg);
}

std::future<bool> MediaGateway::sendPacket(const VoicePacket &packet)
{
    auto data = toBytes(packet);
    return connectionData_->socket->sendData(data);
}

std::future<VoicePacket> MediaGateway::receivePacket()
{
    return std::async(std::launch::async, [this]() -> VoicePacket {
        auto data = connectionData_->socket->receiveData().get();
        VoicePacket packet;
        fromBytes(data, packet);
        return packet;
    });
}

void MediaGateway::onVoiceStateUpdated(const VoiceState &voiceState)
{
    if (voiceState.guildId != guildId_ && voiceState.channelId != channelId_)
        return;
    if (voiceState.userId == currentUserId_)
    {
        if (!connectionData_->currentState)
            connectionData_->currentState = std::make_unique<VoiceState>(voiceState);

        checkReconnectNeeded();
    }
    if (connectionData_->callbacks.voiceUpdate)
        connectionData_->callbacks.voiceUpdate(voiceState);
}

void MediaGateway::onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate)
{
    if (voiceServerUpdate.guildId != guildId_)
        return;
    if (!connectionData_->currentServer)
        connectionData_->currentServer = std::make_unique<VoiceServerUpdateEvent>(voiceServerUpdate);

    checkReconnectNeeded();
}

void MediaGateway::onMessage(const MediaPayload &payload)
{
    switch (payload.opCode)
    {
        case MediaOpCode::Ready:
        {
            auto ready = payload.data.get<VoiceReadyEvent>();
            connectionData_->socket->relocate(ready.ip, ready.port, ready.ssrc);
            connectionData_->socket->start();
            break;
        }
        case MediaOpCode::SessionDescription:
        {
            auto desc = payload.data.get<SessionDescription>();
            if (connectionData_->mode != desc.mode)
            {
                // Assert that or smth
            }
            connectionData_->secretKey = desc.secretKey;
            state_ = ConnectionState::Connected;
            connectionData_->awaitConnectionDone.test_and_set();
            connectionData_->awaitConnectionDone.notify_one();
            break;
        }
        case MediaOpCode::Speaking:
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

void MediaGateway::log(std::string msg)
{
    auto fullMessage = fmt::format("[MediaGateway(Guild: {}, Channel: {})] {}",
        guildId_.to_string(), connectionData_->websocket->getChannelId().to_string(), msg);
    std::cout << fullMessage << std::endl;
}

void MediaGateway::selectProtocol(std::string ip, uint16_t port)
{
    if (connectionData_->callbacks.modeSelector)
        connectionData_->mode = connectionData_->callbacks.modeSelector(connectionData_->websocket->getAwailableModes());
    else
        connectionData_->mode = "xsalsa20_poly1305_lite";
    SelectProtocol::SelectProtocolData protocolData = {
        .address = ip,
        .port = port,
        .mode = connectionData_->mode,
    };
    nlohmann::json data = SelectProtocol {
        .protocol = "udp",
        .data = protocolData
    };
    auto payload = MediaPayload {
        .opCode = MediaOpCode::SelectProtocol,
        .data = data
    };
    send(payload);
    log("SelectProtocol sended");
}

MediaGateway::ConnectionState MediaGateway::getState()
{
    return state_;
}

adb::types::SFID MediaGateway::getGuildId() const
{
    return guildId_;
}

std::optional<adb::types::SFID> MediaGateway::getChannelId() const
{
    return channelId_;
}

std::optional<VoiceState> MediaGateway::getCurrentState() const
{
    if (connectionData_->currentState)
        return *connectionData_->currentState;
    return std::nullopt;
}

const std::string &MediaGateway::getMode()
{
    return connectionData_->mode;
}

void MediaGateway::subscribe()
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
    connectionData_->websocket->setMessageHandler([this](const MediaPayload &payload)
    {
        onMessage(payload);
    });
}

void MediaGateway::checkReconnectNeeded()
{
    if (!connectionData_->currentState || !connectionData_->currentServer)
        return;
    if (state_ == ConnectionState::Connecting)
    {
        auto dthread = std::thread([this]()
        {
            auto future = connectionData_->websocket->connect(
                channelId_.value(), connectionData_->currentServer->endpoint ? *connectionData_->currentServer->endpoint : std::string {},
                connectionData_->currentState->sessionId, connectionData_->currentServer->token);
            auto result = future.get();
            log(fmt::format("Websocket connected: {}", result));
            if (result)
                connectionData_->awaitConnectionResult.test_and_set();
            else
                connectionData_->awaitConnectionResult.clear();
            connectionData_->awaitConnectionDone.test_and_set();
            connectionData_->awaitConnectionDone.notify_one();
        });
        dthread.detach();
    }
}