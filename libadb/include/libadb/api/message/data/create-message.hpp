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
    /**
     * @brief Create Message Params
     * @details https://discord.com/developers/docs/resources/channel#create-message-jsonform-params
     * Note that when sending a message, you must provide a value for at least one of content, embeds, or files[n].
     */
    struct CreateMessageParams
    {
        /// the message contents (up to 2000 characters)
        std::optional<std::string> content;
        /// true if this is a TTS message
        std::optional<bool> tts;
        /// embedded rich content (up to 6000 characters)
        std::optional<std::vector<Embed>> embeds;
        /// allowed mentions for the message
        std::optional<AllowedMentions> allowedMentions;
        /// include to make your message a reply
        std::optional<MessageReference> messageReference;
        /// the components to include with the message
        std::optional<std::vector<MessageComponent>> components;
        /// IDs of up to 3 stickers in the server to send in the message
        std::optional<std::vector<adb::types::SFID>> stickerIds;
        /// attachment objects with filename and description
        std::optional<std::vector<SendAttachment>> attachments;
        /// message flags combined as a bitfield (only SUPPRESS_EMBEDS can be set)
        MessageFlags flags;
    };

    LIBADB_API void to_json(nlohmann::json& j, const CreateMessageParams& params);
}