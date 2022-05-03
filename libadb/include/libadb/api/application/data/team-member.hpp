#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/membership-state.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <string>

namespace adb::api
{
    /**
     * @brief Team Member
     * @details https://discord.com/developers/docs/topics/teams#data-models-team-member-object
     */
    struct TeamMember
    {
        /// the user's membership state on the team
        MembershipState membershipState;
        /// will always be ["*"]
        std::vector<std::string> permissions;
        /// the id of the parent team of which they are a member
        adb::types::SFID teamId;
        /// the avatar, discriminator, id, and username of the user
        User user;
    };

    LIBADB_API void to_json(nlohmann::json& j, const TeamMember& member);
    LIBADB_API void from_json(const nlohmann::json& j, TeamMember& member);
}