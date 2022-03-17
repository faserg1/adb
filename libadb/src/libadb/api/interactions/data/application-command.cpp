#include <libadb/api/interactions/data/application-command.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ApplicationCommand& command)
{
    j = nlohmann::json
    {
        {"id", command.id},
        {"type", command.type},
        {"application_id", command.applicationId},
        {"name", command.name},
        {"description", command.description},
        {"version", command.version},
    };
    map_to_json(j, "guild_id", command.guildId);
    map_to_json(j, "options", command.options);
    map_to_json(j, "default_permission", command.defaultPermission);
}

void adb::api::from_json(const nlohmann::json& j, ApplicationCommand& command)
{
    j.at("id").get_to(command.id);
    j.at("type").get_to(command.type);
    j.at("application_id").get_to(command.applicationId);
    j.at("name").get_to(command.name);
    j.at("description").get_to(command.description);
    j.at("version").get_to(command.version);
    map_from_json(j, "guild_id", command.guildId);
    map_from_json(j, "options", command.options);
    map_from_json(j, "default_permission", command.defaultPermission);
}