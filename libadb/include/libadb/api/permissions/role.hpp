#pragma once

#include <optional>
#include <string>
#include <libadb/api/permissions/permissions.hpp>
#include <libadb/api/permissions/role-tags.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/color.hpp>
#include <libadb/resource/image.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Role Object
     * @details https://discord.com/developers/docs/topics/permissions#role-object
     */
    struct Role
    {
        adb::types::SFID id;
        std::string name;
        adb::types::Color color;
        bool hoist;
        std::optional<adb::types::Nullable<adb::resource::Image>> icon;
        std::optional<adb::types::Nullable<std::string>> unicodeEmoji;
        int64_t position;
        Permissions permissions;
        bool managed;
        bool mentionable;
        std::optional<RoleTags> tags;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Role& role);
    LIBADB_API void from_json(const nlohmann::json& j, Role& role);
}