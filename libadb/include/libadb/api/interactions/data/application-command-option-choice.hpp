#pragma once

#include <string>
#include <variant>

#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /** @brief Application Command Option Choice
     * If you specify choices for an option, they are the only valid values for a user to pick
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-choice-structure
     */
    struct ApplicationCommandOptionChoice
    {
        /// 1-100 character choice name
        std::string name;
        /// value of the choice, up to 100 characters if string
        std::variant<std::string, int64_t, long double> value;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ApplicationCommandOptionChoice& choice);
    LIBADB_API void from_json(const nlohmann::json& j, ApplicationCommandOptionChoice& choice);
}