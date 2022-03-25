#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/permissions/permissions.hpp>
#include <libadb/resource/image-data.hpp>
#include <libadb/types/color.hpp>
#include <libadb/types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Create Guild Role Params
     * @details https://discord.com/developers/docs/resources/guild#create-guild-role
     */
    struct CreateGuildRoleParams
    {
        /// name of the role
        /// default: "new role"
        std::optional<std::string> name;
        /// bitwise value of the enabled/disabled permissions
        /// default: @everyone permissions in guild
        std::optional<Permissions> permissions;
        /// RGB color value
        /// default: 0
        std::optional<adb::types::Color> color;
        /// whether the role should be displayed separately in the sidebar
        /// default: false
        std::optional<bool> hoist;
        /// the role's icon image (if the guild has the ROLE_ICONS feature)
        /// default: null
        std::optional<adb::types::Nullable<adb::resource::ImageData>> icon;
        /// the role's unicode emoji as a standard emoji (if the guild has the ROLE_ICONS feature)
        /// default: null
        std::optional<adb::types::Nullable<std::string>> unicodeEmoji;
        /// whether the role should be mentionable
        /// default: false
        std::optional<bool> mentionable;
    };

    LIBADB_API void to_json(nlohmann::json& j, const CreateGuildRoleParams& params);
    LIBADB_API void from_json(const nlohmann::json& j, CreateGuildRoleParams& params);
}