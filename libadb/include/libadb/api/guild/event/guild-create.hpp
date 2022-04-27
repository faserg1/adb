#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/guild/data/guild.hpp>
#include <libadb/api/guild/data/guild-member.hpp>
#include <libadb/api/channel/data/channel.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/time.hpp>
#include <libadb/api/media/data/voice-state.hpp>
#include <optional>
#include <string>
#include <vector>

namespace adb::api
{
    /**
     * @brief The Guild Object for GUILD_CREATE with extra fields
     * @details https://discord.com/developers/docs/resources/guild#guild-resource
     */
    struct GuildCreate : Guild
    {
        /// when this guild was joined at
        std::optional<adb::types::TimePoint> joinedAt;
        /// true if this is considered a large guild
        std::optional<bool> large;
        /// true if this guild is unavailable due to an outage
        std::optional<bool> unavailable;
        /// total number of members in this guild
        std::optional<int> memberCount;
        /// states of members currently in voice channels; lacks the `guild_id` key
        std::optional<std::vector<VoiceState>> voiceStates;
        /// users in the guild
        std::optional<std::vector<GuildMember>> members;
        /// channels in the guild
        std::optional<std::vector<Channel>> channels;
        /// all active threads in the guild that current user has permission to view
        std::optional<std::vector<Channel>> threads;
        // TODO: presences, etc...
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildCreate& guild);
    LIBADB_API void from_json(const nlohmann::json& j, GuildCreate& guild);
}