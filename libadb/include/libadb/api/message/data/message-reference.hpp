#pragma once

#include <optional>

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    struct MessageReference
    {
        std::optional<adb::types::SFID> messageId;
        std::optional<adb::types::SFID> channelId;
        std::optional<adb::types::SFID> guildId;
        std::optional<bool> failIfNotExists;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageReference& mention);
    LIBADB_API void from_json(const nlohmann::json& j, MessageReference& mention);
}