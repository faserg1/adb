#include <libadb/api/interactions/data/create-application-command-params.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const CreateApplicationCommandParams& params)
{
    j = nlohmann::json
    {
        {"name", params.name},
        {"description", params.description}
    };
    map_to_json(j, "options", params.options);
    map_to_json(j, "default_permission", params.defaultPermission);
    map_to_json(j, "type", params.type);
}

void adb::api::from_json(const nlohmann::json& j, CreateApplicationCommandParams& params)
{
    j.at("name").get_to(params.name);
    j.at("description").get_to(params.description);
    map_from_json(j, "options", params.options);
    map_from_json(j, "default_permission", params.defaultPermission);
    map_from_json(j, "type", params.type);
}