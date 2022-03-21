#include <libadb/api/interactions/data/interaction-data.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;


void adb::api::to_json(nlohmann::json& j, const InteractionDataApplicationCommand& appCommand)
{
    // todo:
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataApplicationCommand& appCommand)
{
    j.at("id").get_to(appCommand.id);
    j.at("name").get_to(appCommand.name);
    j.at("type").get_to(appCommand.type);
}

void adb::api::to_json(nlohmann::json& j, const InteractionDataComponent& dataComponent)
{
    // todo:
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataComponent& dataComponent)
{
    map_from_json(j, "custom_id", dataComponent.customId);
    j.at("component_type").get_to(dataComponent.componentType);
    map_from_json(j, "values", dataComponent.values);
}