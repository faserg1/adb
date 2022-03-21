#pragma once

#include <vector>
#include <memory>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/interactions/data/message-component.hpp>

namespace adb::api
{
    /**
     * @brief Actions Row Component
     * @details https://discord.com/developers/docs/interactions/message-components#action-rows
     * You can have up to 5 Action Rows per message
     * An Action Row cannot contain another Action Row
     */
    struct ActionRowComponent : MessageComponentBase
    {
        std::vector<MessageComponent> components;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ActionRowComponent& mc);
    LIBADB_API void from_json(const nlohmann::json& j, ActionRowComponent& mc);
    LIBADB_API MessageComponent createActionRow(const ActionRowComponent &ar);
}