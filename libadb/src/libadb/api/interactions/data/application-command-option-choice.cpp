#include <libadb/api/interactions/data/application-command-option-choice.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-variant.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const ApplicationCommandOptionChoice& choice)
{
    j = nlohmann::json
    {
        {"name", choice.name},
        {"value", choice.value},
    };
}

void adb::api::from_json(const nlohmann::json& j, ApplicationCommandOptionChoice& choice)
{
    j.at("name").get_to(choice.name);
    j.at("value").get_to(choice.value);
}