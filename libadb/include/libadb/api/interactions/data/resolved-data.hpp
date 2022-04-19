#pragma once

#include <optional>
#include <unordered_map>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/guild/data/guild-member.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/channel/data/channel.hpp>
#include <libadb/api/permissions/role.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/message/data/attachment.hpp>

namespace adb::api
{
    /**
     * @brief Resolved Data
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-resolved-data-structure
     */
    struct ResolvedData
    {
        /// the ids and User objects
        std::optional<std::unordered_map<adb::types::SFID, User>> users;
        /// the ids and partial Member objects
        std::optional<std::unordered_map<adb::types::SFID, PartialGuildMember>> members;
        /// the ids and Role objects
        std::optional<std::unordered_map<adb::types::SFID, Role>> roles;
        /// the ids and partial Channel objects
        std::optional<std::unordered_map<adb::types::SFID, Channel>> channels;
        /// the ids and partial Message objects
        std::optional<std::unordered_map<adb::types::SFID, Message>> messages;
        /// the ids and attachment objects
        std::optional<std::unordered_map<adb::types::SFID, Attachment>> attachments;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ResolvedData& data);
    LIBADB_API void from_json(const nlohmann::json& j, ResolvedData& data);
}