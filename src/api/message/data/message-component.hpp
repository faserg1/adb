#pragma once

#include <optional>
#include <string>
#include <vector>
#include <api/emoji/data/emoji.hpp>
#include <api/message/data/select-option.hpp>

namespace adb::api
{
    /**
     * @brief Component Type
     * @details https://discord.com/developers/docs/interactions/message-components#component-object-component-types
     */
    enum MessageComponentType : uint32_t
    {
        ActionRow = 1,
        Button = 2,
        SelectMenu = 3
    };

    /**
     * @brief Button Style
     * @details https://discord.com/developers/docs/interactions/message-components#button-object-button-styles
     */
    enum ButtonStyle : uint32_t
    {
        Primary = 1,
        Secondary = 2,
        Success = 3,
        Danger = 4,
        Link = 5
    };

    /**
     * @brief Component Object
     * @details https://discord.com/developers/docs/interactions/message-components#component-object
     */
    struct MessageComponent
    {
        MessageComponentType type;
        std::optional<std::string> customId;
        std::optional<bool> disabled;
        std::optional<ButtonStyle> style;
        std::optional<std::string> label;
        std::optional<Emoji> emoji;
        std::optional<std::string> url;
        std::optional<std::vector<SelectOption>> options;
        std::optional<std::string> placeholder;
        std::optional<int> minValues;
        std::optional<int> maxValues;
        std::optional<std::vector<MessageComponent>> components;
    };

    void to_json(nlohmann::json& j, const MessageComponent& mc);
    void from_json(const nlohmann::json& j, MessageComponent& mc);
}