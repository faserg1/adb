#pragma once

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/interactions/data/application-command-permission-type.hpp>
#include <nlohmann/json_fwd.hpp>


namespace adb::api
{
    /**
     * @brief Application Command Permission
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permissions-structure
     */
    struct ApplicationCommandPermission
    {
        /// the id of the role or user
        adb::types::SFID id;
        /// role or user
        ApplicationCommandPermissionType type;
        /// true to allow, false to disallow
        bool permission;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ApplicationCommandPermission& permission);
    LIBADB_API void from_json(const nlohmann::json& j, ApplicationCommandPermission& permission);
}