#include <libadb/api/interactions/data/action-row-component.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <nlohmann/json.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ActionRowComponent& mc)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::ActionRow},
        {"components", mc.components}
    };
}

void adb::api::from_json(const nlohmann::json& j, ActionRowComponent& mc)
{
    j.at("type").get_to(mc.type);
    j.at("components").get_to(mc.components);
}

MessageComponent adb::api::createActionRow(const ActionRowComponent &ar)
{
    auto ptr = std::make_shared<ActionRowComponent>(ar);
    ptr->type = MessageComponentType::ActionRow;
    return ptr;
}