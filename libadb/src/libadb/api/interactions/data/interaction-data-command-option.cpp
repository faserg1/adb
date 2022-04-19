#include <libadb/api/interactions/data/interaction-data-command-option.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-variant.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;


void adb::api::to_json(nlohmann::json& j, const InteractionDataCommandOption& option)
{
    j = nlohmann::json {
        {"name", option.name},
        {"type", option.type}
    };
    map_to_json(j, "value", option.value);
    map_to_json(j, "options", option.options);
    map_to_json(j, "focused", option.focused);
}

void adb::api::from_json(const nlohmann::json& j, InteractionDataCommandOption& option)
{
    j.at("name").get_to(option.name);
    j.at("type").get_to(option.type);
    map_from_json(j, "value", option.value);
    map_from_json(j, "options", option.options);
    map_from_json(j, "focused", option.focused);
}