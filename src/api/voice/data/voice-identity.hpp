#pragma once

#include <types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace adb::api
{
    /**
     * @brief Voice Identity
     * @details https://discord.com/developers/docs/topics/voice-connections#establishing-a-voice-websocket-connection-example-voice-identify-payload
     */
    struct VoiceIdentity
    {
        /// also known as guildId
        adb::types::SFID serverId;
        /// user ID
        adb::types::SFID userId;
        /// session ID, received from VoiceState
        std::string sessionId;
        /// token, received from VoiceServerUpdateEvent
        std::string token;
    };

    void to_json(nlohmann::json& j, const VoiceIdentity& identity);
    void from_json(const nlohmann::json& j, VoiceIdentity& identity);
}
