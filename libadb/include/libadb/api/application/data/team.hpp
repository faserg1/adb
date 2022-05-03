#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/team-member.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <string>

namespace adb::api
{
    /**
     * @brief Team
     * @details https://discord.com/developers/docs/topics/teams#data-models-team-object
     */
    struct Team
    {
        /// the team's icon
        adb::types::Nullable<adb::resource::Image> icon;
        /// the unique id of the team
        adb::types::SFID id;
        /// the members of the team
        std::vector<TeamMember> members;
        /// the name of the team
        std::string name;
        /// the user id of the current team owner
        adb::types::SFID ownerUserId;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Team& team);
    LIBADB_API void from_json(const nlohmann::json& j, Team& team);
}