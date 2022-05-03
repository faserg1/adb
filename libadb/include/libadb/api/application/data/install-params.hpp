#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/permissions/permissions.hpp>
#include <string>
#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Install Params
     * @details https://discord.com/developers/docs/resources/application#install-params-object
     */
    struct InstallParams
    {
        /// the scopes to add the application to the server with
        std::vector<std::string> scopes;
        /// the permissions to request for the bot role
        Permissions permissions;
    };

    LIBADB_API void to_json(nlohmann::json& j, const InstallParams& params);
    LIBADB_API void from_json(const nlohmann::json& j, InstallParams& params);
}