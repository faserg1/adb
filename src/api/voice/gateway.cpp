#include <api/voice/gateway.hpp>
#include <api/gateway/gateway.hpp>
#include <api/gateway/gateway-events.hpp>
#include <api/gateway/data/payload.hpp>
#include <api/voice/data/voice-server-update-event.hpp>
#include <api/voice/data/voice-state.hpp>
#include <nlohmann/json.hpp>
#include <stdexcept>

using namespace adb::api;

template <class Type>
using SharedPromise = std::shared_ptr<std::promise<std::shared_ptr<Type>>>;

struct VoiceGateway::ConnectionData
{
    std::jthread connectionThread;
    std::jthread heartbeatThread;
    std::unique_ptr<adb::types::Subscription> voiceStateSubscription;
    std::unique_ptr<adb::types::Subscription> voiceServerUpdateSubscription;
    VoiceState currentState;

    std::promise<bool> connectionPromise;
};


VoiceGateway::VoiceGateway(std::shared_ptr<Gateway> gateway, adb::types::SFID guildId) :
    gateway_(gateway), connectionData_(std::make_unique<ConnectionData>()), guildId_(guildId)
{
    if (!(gateway_->getIntents() & Intent::GuildVoiceStates))
    {
        throw std::runtime_error("Gateway should be connected with \"GuildVoiceStates\" intent!");
    }
    subscribe();
}

VoiceGateway::~VoiceGateway() = default;

std::future<bool> VoiceGateway::connect(adb::types::SFID channelId, bool mute, bool deaf, bool force)
{
    // если мы уже подключились или подклчаемся к какому-то каналу, мы не можем без флага force его сменить
    if ((state_ == ConnectionState::Connected || state_ == ConnectionState::Connecting) && channelId != channelId_ && !force)
        return std::async(std::launch::deferred, [](){return false;});

    if (state_ == ConnectionState::Disconnected) {
        state_ = ConnectionState::Connecting;
    }
    channelId_ = channelId;

    nlohmann::json data = VoiceStateUpdate {
        .guildId = guildId_,
        .channelId = std::make_shared<adb::types::SFID>(channelId),
        .selfMute = mute,
        .selfDeaf = deaf
    };
    
    gateway_->send(Payload {
        .op = GatewayOpCode::VoiceStateUpdate,
        .data = data
    });

    return std::async(std::launch::deferred, [](){return false;});
}

void VoiceGateway::disconnect()
{
    nlohmann::json data = VoiceStateUpdate {
        .guildId = guildId_,
        .channelId = nullptr,
        .selfMute = connectionData_->currentState.selfMute,
        .selfDeaf = connectionData_->currentState.selfDeaf
    };

    gateway_->send(Payload {
        .op = GatewayOpCode::VoiceStateUpdate,
        .data = data
    });
}

void VoiceGateway::onVoiceStateUpdated(const VoiceState &voiceState)
{
    int i = 0;
}

void VoiceGateway::onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate)
{
    int i = 0;
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