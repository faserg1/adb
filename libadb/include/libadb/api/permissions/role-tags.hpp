#pragma once

#include <libadb/libadb.hpp>
#include <optional>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    struct RoleTags
    {
        /// the id of the bot this role belongs to
        std::optional<adb::types::SFID> botId;
        /// the id of the integration this role belongs to
        std::optional<adb::types::SFID> integrationId;
        /// whether this is the guild's premium subscriber role
        bool premiumSubscriber;
    };

    LIBADB_API void to_json(nlohmann::json& j, const RoleTags& tags);
    LIBADB_API void from_json(const nlohmann::json& j, RoleTags& tags);
}