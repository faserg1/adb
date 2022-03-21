#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/api/interactions/data/message-component.hpp>
#include <libadb/api/interactions/data/message-component-type.hpp>
#include <libadb/api/interactions/data/button-style.hpp>

namespace adb::api
{
    struct ButtonComponent : MessageComponentBase
    {
        ButtonStyle style;
        std::optional<std::string> label;
        std::optional<Emoji> emoji;
        std::optional<std::string> customId;
        std::optional<std::string> url;
        std::optional<bool> disabled;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ButtonComponent& bc);
    LIBADB_API void from_json(const nlohmann::json& j, ButtonComponent& bc);
    LIBADB_API MessageComponent createButton(const ButtonComponent &b);
}