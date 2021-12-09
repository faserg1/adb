#pragma once

#include <optional>
#include <string>
#include <api/emoji/data/emoji.hpp>

namespace adb::api
{
    /**
     * @brief Select Option Object
     * @details https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure
     */
    struct SelectOption
    {
        /// the user-facing name of the option, max 100 character
        std::string label;
        /// the dev-define value of the option, max 100 characters
        std::string value;
        /// an additional description of the option, max 100 characters
        std::optional<std::string> description;
        /// partial emoji object => id, name, and animated
        std::optional<Emoji> emoji;
        /// will render this option as selected by default
        std::optional<bool> isDefault;
    };

    void to_json(nlohmann::json& j, const SelectOption& op);
    void from_json(const nlohmann::json& j, SelectOption& op);
}