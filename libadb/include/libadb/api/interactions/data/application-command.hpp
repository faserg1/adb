#pragma once

#include <string>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/interactions/data/application-command-type.hpp>
#include <libadb/api/interactions/data/application-command-option.hpp>
#include <libadb/resource/localization-map.hpp>

namespace adb::api
{
    /**
     * @brief Application Command Options
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object
     */
    struct ApplicationCommand
    {
        /// unique id of the command
        adb::types::SFID id;
        /// the type of command, defaults 1 if not set
        std::optional<ApplicationCommandType> type;
        /// unique id of the parent application
        adb::types::SFID applicationId;
        /// guild id of the command, if not global
        std::optional<adb::types::SFID> guildId;
        /// 1-32 character name
        std::string name;
        /// Localization dictionary for the name field. Values follow the same restrictions as name
        std::optional<adb::resource::LocalizationMap> nameLocalizations;
        /// 1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands
        std::string description;
        /// Localization dictionary for the description field. Values follow the same restrictions as description
        std::optional<adb::resource::LocalizationMap> descriptionLocalizations;
        /// the parameters for the command, max 25, awailable for CHAT_INPUT commands only
        std::optional<std::vector<ApplicationCommandOption>> options;
        /// whether the command is enabled by default when the app is added to a guild
        std::optional<bool> defaultPermission;
        /// autoincrementing version identifier updated during substantial record changes
        adb::types::SFID version;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ApplicationCommand& command);
    LIBADB_API void from_json(const nlohmann::json& j, ApplicationCommand& command);
}