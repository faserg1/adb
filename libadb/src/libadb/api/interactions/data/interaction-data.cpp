#include <libadb/api/interactions/data/interaction-data.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;


void adb::api::to_json(nlohmann::json& j, const InteractionDataApplicationCommand& appCommand)
{
    j = nlohmann::json
    {
        {"id", appCommand.id},
        {"name", appCommand.name},
        {"type", appCommand.type},
    };
    map_to_json(j, "resolved", appCommand.resolved);
    map_to_json(j, "options", appCommand.options);
    map_to_json(j, "guild_id", appCommand.guildId);
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataApplicationCommand& appCommand)
{
    j.at("id").get_to(appCommand.id);
    j.at("name").get_to(appCommand.name);
    j.at("type").get_to(appCommand.type);
    map_from_json(j, "resolved", appCommand.resolved);
    map_from_json(j, "options", appCommand.options);
    map_from_json(j, "guild_id", appCommand.guildId);
}

void adb::api::to_json(nlohmann::json& j, const InteractionDataComponent& dataComponent)
{
    j = nlohmann::json {};
    map_to_json(j, "custom_id", dataComponent.customId);
    j["component_type"] = dataComponent.componentType;
    map_to_json(j, "values", dataComponent.values);
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataComponent& dataComponent)
{
    map_from_json(j, "custom_id", dataComponent.customId);
    j.at("component_type").get_to(dataComponent.componentType);
    map_from_json(j, "values", dataComponent.values);
}

void adb::api::to_json(nlohmann::json& j, const InteractionDataModal& modal)
{
    map_to_json(j, "custom_id", modal.customId);
    map_to_json(j, "components", modal.components);
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataModal& modal)
{
    map_from_json(j, "custom_id", modal.customId);
    map_from_json(j, "components", modal.components);
}