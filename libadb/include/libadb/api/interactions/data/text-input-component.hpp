#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/interactions/data/text-input-style.hpp>
#include <libadb/api/interactions/data/message-component.hpp>
#include <libadb/api/interactions/data/message-component-type.hpp>

namespace adb::api
{
    /**
     * @brief Text Input Component
     * @details https://discord.com/developers/docs/interactions/message-components#text-inputs-text-input-structure
     */
    struct TextInputComponent : MessageComponentBase
    {
        /// a developer-defined identifier for the input, max 100 characters
        std::string customId;
        /// the Text Input Style
        TextInputStyle style;
        /// the label for this component
        std::string label;
        /// the minimum input length for a text input, min 0, max 4000
        std::optional<uint32_t> minLength;
        /// the maximum input length for a text input, min 1, max 4000
        std::optional<uint32_t> maxLength;
        /// whether this component is required to be filled, default true
        std::optional<bool> required;
        /// a pre-filled value for this component, max 4000 characters
        std::optional<std::string> value;
        /// custom placeholder text if the input is empty, max 100 characters
        std::optional<std::string> placeholder;
    };

    LIBADB_API void to_json(nlohmann::json& j, const TextInputComponent& textInput);
    LIBADB_API void from_json(const nlohmann::json& j, TextInputComponent& textInput);
    LIBADB_API MessageComponent createTextInput(const TextInputComponent &ti);
}