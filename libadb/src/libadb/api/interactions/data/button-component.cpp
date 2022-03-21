#include <libadb/api/interactions/data/button-component.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ButtonComponent& bc)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::Button},
        {"style", bc.style}
    };
    map_to_json(j, "label", bc.label);
    map_to_json(j, "emoji", bc.emoji);
    map_to_json(j, "custom_id", bc.customId);
    map_to_json(j, "url", bc.url);
    map_to_json(j, "disabled", bc.disabled);
}

void adb::api::from_json(const nlohmann::json& j, ButtonComponent& bc)
{
    j.at("type").get_to(bc.type);
    j.at("style").get_to(bc.style);
    map_from_json(j, "label", bc.label);
    map_from_json(j, "emoji", bc.emoji);
    map_from_json(j, "custom_id", bc.customId);
    map_from_json(j, "url", bc.url);
    map_from_json(j, "disabled", bc.disabled);
}

MessageComponent adb::api::createButton(const ButtonComponent &b)
{
    auto ptr = std::make_shared<ButtonComponent>(b);
    ptr->type = MessageComponentType::Button;
    return ptr;
}