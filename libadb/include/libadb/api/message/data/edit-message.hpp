#pragma once

#include <string>
#include <optional>
#include <vector>

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
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
     * @brief Edit Message Params
     * @details https://discord.com/developers/docs/resources/channel#edit-message-jsonform-params
     * 
     */
    struct EditMessageParams
    {
        /// the message contents (up to 2000 characters)
        std::optional<adb::types::Nullable<std::string>> content;
        /// embedded rich content (up to 6000 characters)
        std::optional<adb::types::Nullable<std::vector<Embed>>> embeds;
        /// edit the flags combined as a bitfield (only SUPPRESS_EMBEDS can be set)
        std::optional<adb::types::Nullable<MessageFlags>> flags;
        /// allowed mentions for the message
        std::optional<adb::types::Nullable<AllowedMentions>> allowedMentions;
        /// the components to include with the message
        std::optional<adb::types::Nullable<std::vector<MessageComponent>>> components;
        /// attachment objects with filename and description
        std::optional<adb::types::Nullable<std::vector<SendAttachment>>> attachments;
        
    };

    LIBADB_API void to_json(nlohmann::json& j, const EditMessageParams& params);
}