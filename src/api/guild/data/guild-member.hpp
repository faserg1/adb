#pragma once

#include <optional>
#include <string>
#include <vector>
#include <types/chrono.hpp>
#include <types/snowflake.hpp>
#include <types/time.hpp>
#include <api/user/data/user.hpp>
#include <api/permissions/permissions.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Guild Member Object
     * @details https://discord.com/developers/docs/resources/guild#guild-member-object
     */
    struct GuildMember
    {
        std::optional<User> user;
        std::optional<std::string> nick;
        std::optional<std::string> avatarHash;
        std::vector<adb::types::SFID> roleIds;
        adb::types::TimePoint joinedAt;
        std::optional<adb::types::TimePoint> premiumSince;
        bool deaf;
        bool mute;
        std::optional<bool> pending;
        std::optional<Permissions> permissions;
        std::optional<adb::types::TimePoint> communicationDisabledUntil;
    };

    void to_json(nlohmann::json& j, const GuildMember& guildMember);
    void from_json(const nlohmann::json& j, GuildMember& guildMember);
}