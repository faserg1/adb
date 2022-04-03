#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief Sent when a user removes a reaction from a message.
     * @details https://discord.com/developers/docs/topics/gateway#message-reaction-remove
     */
    struct MessageReactionRemove
    {
        /// the id of the user
        adb::types::SFID userId;
        /// the id of the channel
        adb::types::SFID channelId;
        /// the id of the message
        adb::types::SFID messageId;
        /// the id of the guild
        std::optional<adb::types::SFID> guildId;
        /// the emoji used to react
        Emoji emoji;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageReactionRemove& reactionRemove);
    LIBADB_API void from_json(const nlohmann::json& j, MessageReactionRemove& reactionRemove);
}