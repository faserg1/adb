#pragma once

#include <libadb/types/snowflake.hpp>
#include <optional>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/guild/data/guild-member.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/interactions/data/interaction-type.hpp>
#include <libadb/api/interactions/data/interaction-data.hpp>

namespace adb::api
{
    /**
     * @brief Interaction Object
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object
     */
    struct Interaction
    {
        /// id of the interaction
        adb::types::SFID id;
        /// id of the application this interaction is for
        adb::types::SFID applicationId;
        /// the type of interaction
        InteractionType type;
        /// the command data payload
        std::optional<std::shared_ptr<InteractionData>> data;
        /// the guild it was sent from
        std::optional<adb::types::SFID> guildId;
        /// the channel it was sent from
        std::optional<adb::types::SFID> channelId;
        /// guild member data for the invoking user, including permissions
        std::optional<GuildMember> guildMember;
        /// user object for the invoking user, if invoked in a DM
        std::optional<User> user;
        /// a continuation token for responding to the interaction
        std::string token;
        /// read-only property, always 1
        uint32_t version;
        /// for components, the message they were attached to
        std::optional<Message> message;
        /// the selected language of the invoking user
        std::optional<std::string> locale;
        /// the guild's preferred locale, if invoked in a guild
        std::optional<std::string> guildLocale;
    };

    void to_json(nlohmann::json& j, const Interaction& interaction);
    void from_json(const nlohmann::json& j, Interaction& interaction);

}