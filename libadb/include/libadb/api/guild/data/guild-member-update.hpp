#pragma once

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/time.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/api/user/data/user.hpp>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Sent when a guild member is updated. This will also fire when the user object of a guild member changes.
     * @details https://discord.com/developers/docs/topics/gateway#guild-member-update
     */
    struct GuildMemberUpdate
    {
        /// the id of the guild
        adb::types::SFID guildId;
        std::vector<adb::types::SFID> roleIds;
        User user;
        std::optional<adb::types::Nullable<std::string>> nick;
        adb::types::Nullable<adb::resource::Image> avatar;
        std::optional<adb::types::Nullable<adb::types::TimePoint>> joinedAt;
        std::optional<adb::types::Nullable<adb::types::TimePoint>> premiumSince;
        std::optional<bool> deaf;
        std::optional<bool> mute;
        std::optional<bool> pending;
        std::optional<adb::types::Nullable<adb::types::TimePoint>> communicationDisabledUntil;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildMemberUpdate& guildMemberUpdate);
    LIBADB_API void from_json(const nlohmann::json& j, GuildMemberUpdate& guildMemberUpdate);
}