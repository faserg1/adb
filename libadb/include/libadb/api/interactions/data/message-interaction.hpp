#pragma once

#include <optional>
#include <string>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/interactions/data/interaction-type.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/guild/data/guild-member.hpp>

namespace adb::api
{
    /**
     * @brief Message interaction
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#message-interaction-object
     */
    struct MessageInteraction
    {
        /// id of the interaction
        adb::types::SFID id;
        /// the type of interaction
        InteractionType type;
        /// the name of the application command
        std::string name;
        /// the user who invoked the interaction
        User user;
        /// the member who invoked the interaction in the guild
        std::optional<GuildMember> guildMember;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageInteraction& msgInteraction);
    LIBADB_API void from_json(const nlohmann::json& j, MessageInteraction& msgInteraction);
}