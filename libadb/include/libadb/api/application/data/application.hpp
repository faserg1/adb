#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/application-flags.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/resource/image.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <vector>
#include <string>

namespace adb::api
{
    /**
     * @brief Application
     * @details https://discord.com/developers/docs/resources/application#application-object
     */
    struct Application
    {
        /// 
        adb::types::SFID id;
        /// 
        std::string name;
        /// 
        adb::types::Nullable<adb::resource::Image> icon;
        /// 
        std::string description;
        /// 
        std::optional<std::vector<std::string>> rpcRegions;
        /// 
        bool botPublic;
        bool botRequireCodeGrant;
        std::optional<std::string> termsOfServiceUrl;
        std::optional<std::string> privacyPolicyUrl;
        std::optional<User> owner;
        std::string verifyKey;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Application& app);
    LIBADB_API void from_json(const nlohmann::json& j, Application& app);
}