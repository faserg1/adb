#pragma once

#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Voice State Update
     * @details https://discord.com/developers/docs/topics/gateway#update-voice-state-gateway-voice-state-update-structure
     */
    struct VoiceStateUpdate
    {
        /// the guild id this voice state is for
        adb::types::SFID guildId;
        /// the channel id this user is connected to
        adb::types::Nullable<adb::types::SFID> channelId;
        /// whether this user is locally muted
        bool selfMute;
        /// whether this user is locally deafened
        bool selfDeaf;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceStateUpdate& stateUpdate);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceStateUpdate& stateUpdate);
}