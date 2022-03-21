#include <libadb/api/interactions/data/select-menu-component.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const SelectMenuComponent& selectMenu)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::SelectMenu},
        {"custom_id", selectMenu.customId},
        {"options", selectMenu.options},
    };
    map_to_json(j, "placeholder", selectMenu.placeholder);
    map_to_json(j, "min_values", selectMenu.minValues);
    map_to_json(j, "max_values", selectMenu.maxValues);
    map_to_json(j, "disabled", selectMenu.disabled);
}

void adb::api::from_json(const nlohmann::json& j, SelectMenuComponent& selectMenu)
{
    j.at("type").get_to(selectMenu.type);
    j.at("custom_id").get_to(selectMenu.customId);
    j.at("options").get_to(selectMenu.options);
    map_from_json(j, "placeholder", selectMenu.placeholder);
    map_from_json(j, "min_values", selectMenu.minValues);
    map_from_json(j, "max_values", selectMenu.maxValues);
    map_from_json(j, "disabled", selectMenu.disabled);
}

MessageComponent adb::api::createSelectMenu(const SelectMenuComponent &sm)
{
    auto ptr = std::make_shared<SelectMenuComponent>(sm);
    ptr->type = MessageComponentType::SelectMenu;
    return ptr;
}