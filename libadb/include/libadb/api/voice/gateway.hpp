#pragma once

#include <string>
#include <memory>
#include <functional>
#include <future>
#include <stop_token>
#include <optional>
#include <vector>
#include <array>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/voice/data/voice-state-update.hpp>
#include <libadb/api/voice/data/voice-packet.hpp>

namespace adb::api
{
    class Gateway;
    class DiscordApi;
    class UserApi;

    struct VoiceState;
    struct VoiceServerUpdateEvent;
    struct VoicePayload;
    struct VoiceReadyEvent;

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

        void setModeSelectorCallback(std::function<std::string(const std::vector<std::string> &)> modeSelector);
        void setUserSpeakingCallback(std::function<void(adb::types::SFID userId, bool)> userSpeaking);

        bool send(const VoicePayload &msg);
        
        ConnectionState getState();
        adb::types::SFID getGuildId() const;
        std::optional<adb::types::SFID> getChannelId() const;
        const VoiceState &getCurrentState() const;
        const std::string &getMode();

        std::future<bool> sendData(const std::byte *ptr, size_t size);
        std::future<size_t> receiveData(std::byte *ptr, size_t bufferSize);
        void setBufferSize(size_t bufferSize);

        std::future<bool> sendData(const std::vector<std::byte> &data)
        {
            return sendData(data.data(), data.size());
        }

        template <size_t Size>
        std::future<bool> sendData(const std::array<std::byte, Size> &data)
        {
            return sendData(data.data(), Size);
        }

        std::future<std::vector<std::byte>> receiveData();

        std::future<bool> sendPacket(const VoicePacket &packet);
        std::future<VoicePacket> receivePacket();
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
        std::future<bool> ipDiscovery();
        void selectProtocol();

        std::future<bool> startWebSocket();
        std::future<void> stopWebSocket();

        std::future<bool> startHeartbeating(uint64_t intervalms);
        std::future<void> stopHeartbeating();

        std::future<bool> startDataFlow(const VoiceReadyEvent &voiceReady);
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

        size_t bufferSize_ = 4096;
    };
}