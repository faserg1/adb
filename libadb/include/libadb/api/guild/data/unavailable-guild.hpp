#pragma once

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Unavailable Guild
     * @details https://discord.com/developers/docs/resources/guild#unavailable-guild-object
     */
    struct UnavailableGuild
    {
        /// ID of unavailable guild
        adb::types::SFID id;
        /// Unavailable flag
        bool unavailable;
    };

    LIBADB_API void to_json(nlohmann::json& j, const UnavailableGuild& guild);
    LIBADB_API void from_json(const nlohmann::json& j, UnavailableGuild& guild);
}