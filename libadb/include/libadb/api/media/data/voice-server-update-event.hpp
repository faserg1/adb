#pragma once

#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Voice Server Update Event
     * @details https://discord.com/developers/docs/topics/gateway#voice-server-update-voice-server-update-event-fields
     */
    struct VoiceServerUpdateEvent
    {
        /// voice connection token
        std::string token;
        /// the guild this voice server update is for
        adb::types::SFID guildId;
        /// the voice server host
        adb::types::Nullable<std::string> endpoint;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceServerUpdateEvent& serverUpdateEvent);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceServerUpdateEvent& serverUpdateEvent);
}