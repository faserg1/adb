#include <libadb/api/application/data/team.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/resource/image-resolver.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::resource;

void adb::api::to_json(nlohmann::json& j, const Team& team)
{
    j = nlohmann::json
    {
        { "icon", team.icon ? team.icon->getName() : nullptr },
        { "id", team.id },
        { "members", team.members },
        { "name", team.name },
        { "owner_user_id", team.ownerUserId },
    };
}

void adb::api::from_json(const nlohmann::json& j, Team& team)
{
    j.at("id").get_to(team.id);
    if (!j.at("icon").is_null())
        team.icon = ImageResolver::getTeamIcon(team.id, j.at("icon").get<std::string>());
    j.at("members").get_to(team.members);
    j.at("name").get_to(team.name);
    j.at("owner_user_id").get_to(team.ownerUserId);
}