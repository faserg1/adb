#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>

#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Application Command Options
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure
     */
    struct ApplicationCommandOption
    {

    };

    LIBADB_API void to_json(nlohmann::json& j, const ApplicationCommandOption& option);
    LIBADB_API void from_json(const nlohmann::json& j, ApplicationCommandOption& option);
}