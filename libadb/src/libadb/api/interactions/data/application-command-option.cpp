#include <libadb/api/interactions/data/application-command-option.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-variant.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ApplicationCommandOption& option)
{
    j = nlohmann::json
    {
        {"type", option.type},
        {"name", option.name},
        {"description", option.description},
    };
    map_to_json(j, "name_localizations", option.nameLocalizations);
    map_to_json(j, "description_localizations", option.descriptionLocalizations);
    map_to_json(j, "required", option.required);
    map_to_json(j, "choices", option.choices);
    map_to_json(j, "options", option.options);
    map_to_json(j, "channel_types", option.channelTypes);
    map_to_json(j, "min_value", option.minValue);
    map_to_json(j, "max_value", option.maxValue);
    map_to_json(j, "autocomplete", option.autocomplete);
}

void adb::api::from_json(const nlohmann::json& j, ApplicationCommandOption& option)
{
    j.at("type").get_to(option.type);
    j.at("name").get_to(option.name);
    j.at("description").get_to(option.description);
    map_from_json(j, "name_localizations", option.nameLocalizations);
    map_from_json(j, "description_localizations", option.descriptionLocalizations);
    map_from_json(j, "required", option.required);
    map_from_json(j, "choices", option.choices);
    map_from_json(j, "options", option.options);
    map_from_json(j, "channel_types", option.channelTypes);
    map_from_json(j, "min_value", option.minValue);
    map_from_json(j, "max_value", option.maxValue);
    map_from_json(j, "autocomplete", option.autocomplete);
}