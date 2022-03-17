#pragma once

#include <string>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>

#include <libadb/libadb.hpp>
#include <libadb/api/interactions/data/application-command-type.hpp>
#include <libadb/api/interactions/data/application-command-option.hpp>

namespace adb::api
{
    /**
     * @brief Create Global/Guild Application Command
     * @details https://discord.com/developers/docs/interactions/application-commands#endpoints-json-params
     */
    struct CreateApplicationCommandParams
    {
        /// 1-32 character name, must match the following regex ^[\w-]{1,32}$ with the unicode flag set
        std::string name;
        /// 1-100 character description, should be empty for USER and MESSAGE command types
        std::string description;
        /// the parameters for the command, awailable for CHAT_INPUT commands only
        std::optional<std::vector<ApplicationCommandOption>> options;
        /// whether the command is enabled by default when the app is added to a guild
        std::optional<bool> defaultPermission;
        /// the type of command, defaults 1 if not set
        std::optional<ApplicationCommandType> type;
    };

    LIBADB_API void to_json(nlohmann::json& j, const CreateApplicationCommandParams& params);
    LIBADB_API void from_json(const nlohmann::json& j, CreateApplicationCommandParams& params);
}