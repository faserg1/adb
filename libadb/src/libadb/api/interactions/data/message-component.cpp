#include <libadb/api/interactions/data/message-component.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageComponent& mc)
{
    j["type"] = mc.type;
    map_to_json(j, "custom_id", mc.customId);
    map_to_json(j, "disabled", mc.disabled);
    map_to_json(j, "style", mc.style);
    map_to_json(j, "label", mc.label);
    map_to_json(j, "emoji", mc.emoji);
    map_to_json(j, "url", mc.url);
    map_to_json(j, "options", mc.options);
    map_to_json(j, "placeholder", mc.placeholder);
    map_to_json(j, "min_values", mc.minValues);
    map_to_json(j, "max_values", mc.maxValues);
    map_to_json(j, "components", mc.components);
}

void adb::api::from_json(const nlohmann::json& j, MessageComponent& mc)
{
    j.at("type").get_to(mc.type);
    map_from_json(j, "custom_id", mc.customId);
    map_from_json(j, "disabled", mc.disabled);
    map_from_json(j, "style", mc.style);
    map_from_json(j, "label", mc.label);
    map_from_json(j, "emoji", mc.emoji);
    map_from_json(j, "url", mc.url);
    map_from_json(j, "options", mc.options);
    map_from_json(j, "placeholder", mc.placeholder);
    map_from_json(j, "min_values", mc.minValues);
    map_from_json(j, "max_values", mc.maxValues);
    map_from_json(j, "components", mc.components);
}