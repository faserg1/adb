#pragma once

#include <string>
#include <memory>
#include <functional>
#include <future>
#include <stop_token>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <api/voice/data/voice-state-update.hpp>

namespace adb::api
{
    class Gateway;
    class DiscordApi;
    class UserApi;

    struct VoiceState;
    struct VoiceServerUpdateEvent;
    struct VoicePayload;

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
        
        [[nodiscard]] std::future<bool> connect(adb::types::SFID channelId, bool mute, bool deaf, bool force = false);
        [[nodiscard]] std::future<void> disconnect();

        bool send(const VoicePayload &msg);
        
        ConnectionState getState();
        adb::types::SFID getGuildId() const;
        std::optional<adb::types::SFID> getChannelId() const;
        const VoiceState &getCurrentState() const;

    protected:
        VoiceGateway(std::unique_ptr<UserApi> userApi, std::shared_ptr<Gateway> gateway, adb::types::SFID guildId);

        virtual void onPreConnect();
        virtual void onPostConnect();

        virtual void onPreDisconnect();
        virtual void onPostDisconnect();

        virtual void onVoiceStateUpdated(const VoiceState &voiceState);
        virtual void onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate);

        virtual void onMessage(const VoicePayload &payload);
        bool sendInternal(const VoicePayload &msg);
    private:
        void subscribe();

        void configureClient();
        void configureMessageHandler();

        void connectInternal(std::stop_token stop);
        void identity();

        std::future<bool> startWebSocket();
        std::future<void> stopWebSocket();

        std::future<bool> startHeartbeating(uint64_t intervalms);
        std::future<void> stopHeartbeating();

        std::future<bool> startDataFlow();
        std::future<void> stopDataFlow();
    private:
        std::shared_ptr<Gateway> gateway_;
        std::unique_ptr<ConnectionData> connectionData_;
        ConnectionState state_ = ConnectionState::Disconnected;

        std::string sessionId_;
        std::string token_;
        std::string gatewayUrl_;

        adb::types::SFID guildId_;
        adb::types::SFID currentUserId_;
        std::optional<adb::types::SFID> channelId_;
    };
}