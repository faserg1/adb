#pragma once

#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Voice Resume
     * @details https://discord.com/developers/docs/topics/voice-connections#resuming-voice-connection
     */
    struct VoiceResume
    {
        /// also known as guildId
        adb::types::SFID serverId;
        /// session ID, received from VoiceState
        std::string sessionId;
        /// token, received from VoiceServerUpdateEvent
        std::string token;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceResume& resume);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceResume& resume);
}
