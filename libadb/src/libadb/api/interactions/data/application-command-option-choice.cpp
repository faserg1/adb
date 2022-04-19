#include <libadb/api/interactions/data/application-command-option-choice.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-variant.hpp>
#include <libadb/types/helpers/json-optional.hpp>

using namespace adb::api;
using namespace adb::types;
using namespace adb::resource;

void adb::api::to_json(nlohmann::json& j, const ApplicationCommandOptionChoice& choice)
{
    j = nlohmann::json
    {
        {"name", choice.name},
        {"value", choice.value},
    };
    map_to_json(j, "name_localizations", choice.nameLocalizations);
}

void adb::api::from_json(const nlohmann::json& j, ApplicationCommandOptionChoice& choice)
{
    j.at("name").get_to(choice.name);
    j.at("value").get_to(choice.value);
    map_from_json(j, "name_localizations", choice.nameLocalizations);
}