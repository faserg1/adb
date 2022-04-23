#pragma once

#include <vector>
#include <memory>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/interactions/event/component-value.hpp>

namespace adb::api
{
    /**
     * @brief Actions Row Component
     * @details https://discord.com/developers/docs/interactions/message-components#action-rows
     */
    struct ActionRowValue : ComponentValueBase
    {
        std::vector<ComponentValue> components;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ActionRowValue& mc);
    LIBADB_API void from_json(const nlohmann::json& j, ActionRowValue& mc);
}