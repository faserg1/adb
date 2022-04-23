#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/interactions/event/component-value.hpp>
#include <libadb/api/interactions/data/message-component-type.hpp>

namespace adb::api
{
    /**
     * @brief Text Input Component
     * @details https://discord.com/developers/docs/interactions/message-components#text-inputs-text-input-structure
     */
    struct TextInputValue : ComponentValueBase
    {
        /// a developer-defined identifier for the input, max 100 characters
        std::string customId;
        /// a pre-filled value for this component, max 4000 characters
        std::optional<std::string> value;
    };

    LIBADB_API void to_json(nlohmann::json& j, const TextInputValue& textInput);
    LIBADB_API void from_json(const nlohmann::json& j, TextInputValue& textInput);
}