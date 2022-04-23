#include <libadb/api/interactions/event/action-row-value.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <nlohmann/json.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ActionRowValue& mc)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::ActionRow},
        {"components", mc.components}
    };
}

void adb::api::from_json(const nlohmann::json& j, ActionRowValue& mc)
{
    j.at("type").get_to(mc.type);
    j.at("components").get_to(mc.components);
}
