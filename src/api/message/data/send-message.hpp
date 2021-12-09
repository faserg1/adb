#pragma once

#include <string>
#include <optional>
#include <vector>

#include <types/snowflake.hpp>
#include <api/message/data/embed.hpp>
#include <api/message/data/allowed-mentions.hpp>
#include <api/message/data/message-component.hpp>
#include <api/message/data/attachment.hpp>

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

    struct SendMessageParams
    {
        std::string content;
        std::optional<bool> tts;
        std::optional<std::vector<Embed>> embeds;
        std::optional<AllowedMentions> allowedMentions;
        std::optional<MessageReference> messageReference;
        std::optional<std::vector<MessageComponent>> components;
        std::optional<std::vector<adb::types::SFID>> stickerIds;
        std::optional<std::vector<SendAttachment>> attachments;
    };

    void to_json(nlohmann::json& j, const MessageReference& mention);
    void from_json(const nlohmann::json& j, MessageReference& mention);

    void to_json(nlohmann::json& j, const SendMessageParams& params);
    void from_json(const nlohmann::json& j, SendMessageParams& params);
}