#pragma once

#include <vector>
#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/interactions/data/application-command-permission.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Guild Application Command Permissions
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object
     */
    struct GuildApplicationCommandPermissions
    {
        /// the id of the command
        adb::types::SFID id;
        /// the id of the application the command belongs to
        adb::types::SFID applicationId;
        /// the id of the guild
        adb::types::SFID guildId;
        /// the permissions for the command in the guild
        std::vector<ApplicationCommandPermission> permissions;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildApplicationCommandPermissions& permissions);
    LIBADB_API void from_json(const nlohmann::json& j, GuildApplicationCommandPermissions& permissions);
}
