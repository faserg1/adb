#pragma once

#include <string>
#include <variant>
#include <optional>
#include <cstdint>
#include <vector>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/interactions/data/application-command-option-type.hpp>

namespace adb::api
{
    /**
     * @brief Application Command Interaction Data Option
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-interaction-data-option-structure
     */
    struct InteractionDataCommandOption
    {
        /// the name of the parameter
        std::string name;
        /// value of application command option type
        ApplicationCommandOptionType type;
        /// the value of the option resulting from user input
        std::optional<std::variant<int64_t, double, std::string>> value;
        /// present if this option is a group or subcommand
        std::optional<std::vector<InteractionDataCommandOption>> options;
        /// true if this option is the currently focused option for autocomplete
        std::optional<bool> focused;
    };

    LIBADB_API void to_json(nlohmann::json& j, const InteractionDataCommandOption& option);
    LIBADB_API void from_json(const nlohmann::json& j, InteractionDataCommandOption& option);
}