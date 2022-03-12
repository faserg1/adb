#pragma once

#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/media/data/media-stream-description.hpp>

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
        /// should video be enabled [NOT DOCUMENTED!!!]
        std::optional<bool> video;
        /// ???
        std::optional<std::vector<MediaStreamDescription>> streams;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceIdentity& identity);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceIdentity& identity);
}
