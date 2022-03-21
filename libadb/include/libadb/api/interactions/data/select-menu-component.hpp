#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/interactions/data/select-option.hpp>
#include <libadb/api/interactions/data/message-component.hpp>
#include <libadb/api/interactions/data/message-component-type.hpp>

namespace adb::api
{
    /**
     * @brief Select Menu Component
     * @details https://discord.com/developers/docs/interactions/message-components#select-menus
     */
    struct SelectMenuComponent : MessageComponentBase
    {
        /// a developer-defined identifier for the select menu, max 100 characters
        std::string customId;
        /// the choices in the select, max 25
        std::vector<SelectOption> options;
        /// custom placeholder text if nothing is selected, max 150 characters
        std::optional<std::string> placeholder;
        /// the minimum number of items that must be chosen; default 1, min 0, max 25
        std::optional<int> minValues;
        /// the maximum number of items that can be chosen; default 1, max 25
        std::optional<int> maxValues;
        /// disable the select, default false
        std::optional<bool> disabled;
    };

    LIBADB_API void to_json(nlohmann::json& j, const SelectMenuComponent& selectMenu);
    LIBADB_API void from_json(const nlohmann::json& j, SelectMenuComponent& selectMenu);
    LIBADB_API MessageComponent createSelectMenu(const SelectMenuComponent &sm);
}