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
#include <libadb/api/media/data/voice-state-update.hpp>
#include <libadb/api/media/data/voice-packet.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class Gateway;
    class DiscordApi;
    class UserApi;

    struct VoiceState;
    struct VoiceServerUpdateEvent;
    struct MediaPayload;
    struct VoiceReadyEvent;

    class MediaGateway
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
        LIBADB_API ~MediaGateway();
        
        LIBADB_API [[nodiscard]] std::future<bool> connect(adb::types::SFID channelId, bool mute, bool deaf, bool force = false);
        LIBADB_API [[nodiscard]] std::future<void> disconnect();

        LIBADB_API void setModeSelectorCallback(std::function<std::string(const std::vector<std::string> &)> modeSelector);
        LIBADB_API void setUserSpeakingCallback(std::function<void(adb::types::SFID userId, bool)> userSpeaking);
        LIBADB_API void setVoiceStateUpdateCallback(std::function<void(const VoiceState &voiceState)> callback);

        LIBADB_API bool send(const MediaPayload &msg);
        
        LIBADB_API ConnectionState getState();
        LIBADB_API adb::types::SFID getGuildId() const;
        LIBADB_API std::optional<adb::types::SFID> getChannelId() const;
        LIBADB_API std::optional<VoiceState> getCurrentState() const;
        LIBADB_API const std::string &getMode();

        LIBADB_API std::future<bool> sendPacket(const VoicePacket &packet);
        LIBADB_API std::future<VoicePacket> receivePacket();
    protected:
        MediaGateway(std::unique_ptr<UserApi> userApi, std::shared_ptr<Gateway> gateway, adb::types::SFID guildId);

        virtual void onVoiceStateUpdated(const VoiceState &voiceState);
        virtual void onServerUpdated(const VoiceServerUpdateEvent &voiceServerUpdate);

        virtual void onMessage(const MediaPayload &payload);

        void log(std::string msg);
    private:
        void subscribe();

        void selectProtocol(std::string ip, uint16_t port);

        void checkReconnectNeeded();
    private:
        std::shared_ptr<Gateway> gateway_;
        std::unique_ptr<ConnectionData> connectionData_;
        ConnectionState state_ = ConnectionState::Disconnected;

        adb::types::SFID guildId_;
        adb::types::SFID currentUserId_;
        std::optional<adb::types::SFID> channelId_;
    };
}