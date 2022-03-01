#pragma once

#include <string>
#include <memory>
#include <functional>
#include <future>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <api/voice/data/voice-state-update.hpp>

namespace adb::api
{
    class Gateway;
    class DiscordApi;

    struct VoiceState;
    struct VoiceServerUpdateEvent;

    class VoiceGateway
    {
        friend DiscordApi;
        struct ConnectionData;
    public:
        enum class ConnectionState
        {
            Disconnected,
            Connecting,
            Connected
        };
    public:
        ~VoiceGateway();
        
        std::future<bool> connect(adb::types::SFID channelId, bool mute, bool deaf, bool force = false);
        void disconnect();
        
        ConnectionState getState();
        adb::types::SFID getGuildId() const;
        std::optional<adb::types::SFID> getChannelId() const;
        const VoiceState &getCurrentState() const;

    protected:
        VoiceGateway(std::shared_ptr<Gateway> gateway, adb::types::SFID guildId);

        virtual void onVoiceStateUpdated(const VoiceState &voiceState);
        virtual void onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate);
    private:
        void subscribe();
        
    private:
        std::shared_ptr<Gateway> gateway_;
        std::unique_ptr<ConnectionData> connectionData_;
        ConnectionState state_ = ConnectionState::Disconnected;

        std::string token_;
        std::string gatewayUrl_;

        adb::types::SFID guildId_;
        std::optional<adb::types::SFID> channelId_;
    };
}