#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief Sent when a bot removes all instances of a given emoji from the reactions of a message.
     * @details https://discord.com/developers/docs/topics/gateway#message-reaction-remove-emoji
     */
    struct MessageReactionRemoveEmoji
    {
        /// the id of the channel
        adb::types::SFID channelId;
        /// the id of the guild
        std::optional<adb::types::SFID> guildId;
        /// the id of the message
        adb::types::SFID messageId;
        /// the emoji used to react
        Emoji emoji;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageReactionRemoveEmoji& reactionRemove);
    LIBADB_API void from_json(const nlohmann::json& j, MessageReactionRemoveEmoji& reactionRemove);
}