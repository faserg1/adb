#pragma once

#include <string>
#include <optional>
#include <vector>

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/message/data/message-reference.hpp>
#include <libadb/api/message/data/embed.hpp>
#include <libadb/api/message/data/allowed-mentions.hpp>
#include <libadb/api/message/data/attachment.hpp>
#include <libadb/api/message/data/message-flags.hpp>
#include <libadb/api/interactions/data/message-component.hpp>

#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    struct SendMessageParams
    {
        std::optional<std::string> content;
        std::optional<bool> tts;
        std::optional<std::vector<Embed>> embeds;
        std::optional<AllowedMentions> allowedMentions;
        std::optional<MessageReference> messageReference;
        std::optional<std::vector<MessageComponent>> components;
        std::optional<std::vector<adb::types::SFID>> stickerIds;
        std::optional<std::vector<SendAttachment>> attachments;
        MessageFlags flags;
    };

    LIBADB_API void to_json(nlohmann::json& j, const SendMessageParams& params);
    LIBADB_API void from_json(const nlohmann::json& j, SendMessageParams& params);
}