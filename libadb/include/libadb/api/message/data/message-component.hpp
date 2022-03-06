#pragma once

#include <optional>
#include <string>
#include <vector>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/api/message/data/select-option.hpp>
#include <libadb/api/message/data/message-component-type.hpp>
#include <libadb/api/message/data/button-style.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
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

    LIBADB_API void to_json(nlohmann::json& j, const MessageComponent& mc);
    LIBADB_API void from_json(const nlohmann::json& j, MessageComponent& mc);
}