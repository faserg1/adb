#include <libadb/api/interactions/data/interaction-data.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;


void adb::api::to_json(nlohmann::json& j, const InteractionDataApplicationCommand& appCommand)
{

}

void adb::api::from_json(const nlohmann::json& j, InteractionDataApplicationCommand& appCommand)
{

}

void adb::api::to_json(nlohmann::json& j, const InteractionDataComponent& dataComponent)
{

}

void adb::api::from_json(const nlohmann::json& j, InteractionDataComponent& dataComponent)
{
    map_from_json(j, "custom_id", dataComponent.customId);
    j.at("component_type").get_to(dataComponent.componentType);
    map_from_json(j, "values", dataComponent.values);
}