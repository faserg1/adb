#include <libadb/api/application/data/team-member.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const TeamMember& member)
{
    j = nlohmann::json
    {
        { "membership_state", member.membershipState },
        { "permissions", member.permissions },
        { "team_id", member.teamId },
        { "user", member.user },
    };
}

void adb::api::from_json(const nlohmann::json& j, TeamMember& member)
{
    j.at("membership_state").get_to(member.membershipState);
    j.at("permissions").get_to(member.permissions);
    j.at("team_id").get_to(member.teamId);
    j.at("user").get_to(member.user);
}