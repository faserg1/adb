#pragma once

#include <optional>
#include <string>
#include <nlohmann/json_fwd.hpp>
#include <types/snowflake.hpp>
#include <types/time.hpp>
#include <api/user/data/user.hpp>
#include <api/guild/data/guild-member.hpp>
#include <api/channel/data/channel-mention.hpp>
#include <api/message/data/attachment.hpp>

namespace adb::api
{
    /**
     * @brief Message object
     * @details https://discord.com/developers/docs/resources/channel#message-object-message-structure
     */
    struct Message
    {
        adb::types::SFID id;
        adb::types::SFID channelId;
        adb::types::SFID guildId;
        User author;
        std::optional<GuildMember> member;
        std::string content;
        adb::types::TimePoint timestamp;
        std::optional<adb::types::TimePoint> editedTimestamp;
        bool tts;
        bool mentionEveryone;
        std::vector<User> mentions;
        std::vector<adb::types::SFID> mentionRoles;
        std::optional<std::vector<ChannelMention>> channelMentions;
        std::vector<Attachment> attachments;
    };

    void to_json(nlohmann::json& j, const Message& msg);
    void from_json(const nlohmann::json& j, Message& msg);
}