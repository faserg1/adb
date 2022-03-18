#include <libadb/api/interactions/data/guild-application-command-permissions.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const GuildApplicationCommandPermissions& permissions)
{
    j = nlohmann::json
    {
        {"id", permissions.id},
        {"application_id", permissions.applicationId},
        {"guild_id", permissions.guildId},
        {"permissions", permissions.permissions},
    };
}

void adb::api::from_json(const nlohmann::json& j, GuildApplicationCommandPermissions& permissions)
{
    j.at("id").get_to(permissions.id);
    j.at("application_id").get_to(permissions.applicationId);
    j.at("guild_id").get_to(permissions.guildId);
    j.at("permissions").get_to(permissions.permissions);
}