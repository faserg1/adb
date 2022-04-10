#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/guild/data/guild.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/time.hpp>
#include <optional>
#include <string>

namespace adb::api
{
    /**
     * @brief The Guild Object for GUILD_CREATE with extra fields
     * @details https://discord.com/developers/docs/resources/guild#guild-resource
     */
    struct GuildCreate : Guild
    {
        std::optional<adb::types::TimePoint> joinedAt;
        std::optional<bool> large;
        std::optional<bool> unavailable;
        std::optional<int> memberCount;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildCreate& guild);
    LIBADB_API void from_json(const nlohmann::json& j, GuildCreate& guild);
}