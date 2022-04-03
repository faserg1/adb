#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/guild/data/guild-member.hpp>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief Sent when a user adds a reaction to a message.
     * @details https://discord.com/developers/docs/topics/gateway#message-reaction-add
     */
    struct MessageReactionAdd
    {
        /// the id of the user
        adb::types::SFID userId;
        /// the id of the channel
        adb::types::SFID channelId;
        /// the id of the message
        adb::types::SFID messageId;
        /// the id of the guild
        std::optional<adb::types::SFID> guildId;
        /// the member who reacted if this happened in a guild
        std::optional<GuildMember> member;
        /// the emoji used to react
        Emoji emoji;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageReactionAdd& reactionAdd);
    LIBADB_API void from_json(const nlohmann::json& j, MessageReactionAdd& reactionAdd);
}