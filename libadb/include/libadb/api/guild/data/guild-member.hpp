#pragma once

#include <optional>
#include <string>
#include <vector>
#include <libadb/libadb.hpp>
#include <libadb/types/time.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/time.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/permissions/permissions.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Guild Member Object
     * @details https://discord.com/developers/docs/resources/guild#guild-member-object
     */
    struct GuildMember
    {
        /// the user this guild member represents
        /// The field user won't be included in the member object attached to MESSAGE_CREATE and MESSAGE_UPDATE gateway events.
        std::optional<User> user;
        /// this user's guild nickname
        std::optional<adb::types::Nullable<std::string>> nick;
        /// the member's guild avatar hash
        /// NOTE: This field will not have valid Image object until parsed with gm_parse_avatar
        std::optional<adb::types::Nullable<adb::resource::Image>> avatar;
        /// array of role object ids
        std::vector<adb::types::SFID> roleIds;
        /// when the user joined the guild
        adb::types::TimePoint joinedAt;
        /// when the user started boosting the guild
        std::optional<adb::types::Nullable<adb::types::TimePoint>> premiumSince;
        /// whether the user is deafened in voice channels
        bool deaf;
        /// whether the user is muted in voice channels
        bool mute;
        /// whether the user has not yet passed the guild's Membership Screening requirements
        std::optional<bool> pending;
        /// total permissions of the member in the channel, including overwrites, returned when in the interaction object
        std::optional<Permissions> permissions;
        /// when the user's timeout will expire and the user will be able to communicate in the guild again, null or a time in the past if the user is not timed out
        std::optional<adb::types::Nullable<adb::types::TimePoint>> communicationDisabledUntil;
    };

    /**
     * @brief Guild Member Object
     * @details https://discord.com/developers/docs/resources/guild#guild-member-object
     */
    struct PartialGuildMember
    {
        /// the user this guild member represents
        /// The field user won't be included in the member object attached to MESSAGE_CREATE and MESSAGE_UPDATE gateway events.
        std::optional<User> user;
        /// this user's guild nickname
        std::optional<adb::types::Nullable<std::string>> nick;
        /// the member's guild avatar hash
        /// NOTE: This field will not have valid Image object until parsed with gm_parse_avatar
        std::optional<adb::types::Nullable<adb::resource::Image>> avatar;
        /// array of role object ids
        std::optional<std::vector<adb::types::SFID>> roleIds;
        /// when the user joined the guild
        std::optional<adb::types::TimePoint> joinedAt;
        /// when the user started boosting the guild
        std::optional<adb::types::Nullable<adb::types::TimePoint>> premiumSince;
        /// whether the user is deafened in voice channels
        std::optional<bool> deaf;
        /// whether the user is muted in voice channels
        std::optional<bool> mute;
        /// whether the user has not yet passed the guild's Membership Screening requirements
        std::optional<bool> pending;
        /// total permissions of the member in the channel, including overwrites, returned when in the interaction object
        std::optional<Permissions> permissions;
        /// when the user's timeout will expire and the user will be able to communicate in the guild again, null or a time in the past if the user is not timed out
        std::optional<adb::types::Nullable<adb::types::TimePoint>> communicationDisabledUntil;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildMember& guildMember);
    LIBADB_API void from_json(const nlohmann::json& j, GuildMember& guildMember);
    // Provide guildId, and userId if exists, for ensure data is complete
    LIBADB_API void gm_parse_avatar(adb::types::SFID guildId, std::optional<adb::types::SFID> optUserId, 
        const nlohmann::json& jGuildMember, GuildMember& guildMember);

    LIBADB_API void to_json(nlohmann::json& j, const PartialGuildMember& guildMember);
    LIBADB_API void from_json(const nlohmann::json& j, PartialGuildMember& guildMember);
}