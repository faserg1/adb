#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/application-flags.hpp>
#include <libadb/api/application/data/team.hpp>
#include <libadb/api/application/data/install-params.hpp>
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
        /// the id of the app
        adb::types::SFID id;
        /// the name of the app
        std::string name;
        /// the icon of the app
        adb::types::Nullable<adb::resource::Image> icon;
        /// the description of the app
        std::string description;
        /// an array of rpc origin urls, if rpc is enabled
        std::optional<std::vector<std::string>> rpcRegions;
        /// when false only app owner can join the app's bot to guilds
        bool botPublic;
        /// when true the app's bot will only join upon completion of the full oauth2 code grant flow
        bool botRequireCodeGrant;
        /// the url of the app's terms of service
        std::optional<std::string> termsOfServiceUrl;
        /// the url of the app's privacy policy
        std::optional<std::string> privacyPolicyUrl;
        /// partial user object containing info on the owner of the application
        std::optional<User> owner;
        /// the hex encoded key for verification in interactions and the GameSDK's GetTicket
        std::string verifyKey;
        /// if the application belongs to a team, this will be a list of the members of that team
        adb::types::Nullable<Team> team;
        /// if this application is a game sold on Discord, this field will be the guild to which it has been linked
        std::optional<adb::types::SFID> guildId;
        /// if this application is a game sold on Discord, this field will be the id of the "Game SKU" that is created, if exists
        std::optional<adb::types::SFID> primarySkuId;
        /// if this application is a game sold on Discord, this field will be the URL slug that links to the store page
        std::optional<std::string> slug;
        /// the application's default rich presence invite cover image
        std::optional<adb::resource::Image> coverImage;
        /// the application's public flags
        std::optional<ApplicationFlags> flags;
        /// up to 5 tags describing the content and functionality of the application
        std::optional<std::vector<std::string>> tags;
        /// settings for the application's default in-app authorization link, if enabled
        std::optional<InstallParams> installParams;
        /// the application's default custom authorization link, if enabled
        std::optional<std::string> customInstallUrl;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Application& app);
    LIBADB_API void from_json(const nlohmann::json& j, Application& app);
}