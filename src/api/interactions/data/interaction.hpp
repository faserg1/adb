#pragma once

#include <types/snowflake.hpp>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <api/guild/data/guild-member.hpp>
#include <api/user/data/user.hpp>
#include <api/message/data/message.hpp>
#include "interaction-type.hpp"
#include "interaction-data.hpp"

namespace adb::api
{
    /**
     * @brief Interaction Object
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object
     */
    struct Interaction
    {
        adb::types::SFID id;
        adb::types::SFID applicationId;
        InteractionType type;
        // data
        std::optional<adb::types::SFID> guildId;
        std::optional<adb::types::SFID> channelId;
        std::optional<GuildMember> guildMember;
        std::optional<User> user;
        std::string token;
        uint32_t version;
        std::optional<Message> message;
        std::optional<std::string> locale;
        std::optional<std::string> guildLocale;
    };
}