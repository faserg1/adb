#pragma once

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief Sent when a user explicitly removes all reactions from a message.
     * @details https://discord.com/developers/docs/topics/gateway#message-reaction-remove-all
     */
    struct MessageReactionRemoveAll
    {
        /// the id of the channel
        adb::types::SFID channelId;
        /// the id of the message
        adb::types::SFID messageId;
        /// the id of the guild
        std::optional<adb::types::SFID> guildId;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageReactionRemoveAll& reactionRemove);
    LIBADB_API void from_json(const nlohmann::json& j, MessageReactionRemoveAll& reactionRemove);
}