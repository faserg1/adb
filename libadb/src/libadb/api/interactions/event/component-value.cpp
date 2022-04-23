#include <libadb/api/interactions/event/component-value.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/api/interactions/event/action-row-value.hpp>
//#include <libadb/api/interactions/data/select-menu-component.hpp>
#include <libadb/api/interactions/event/text-input-value.hpp>
//#include <libadb/api/interactions/data/button-component.hpp>
using namespace adb::api;
using namespace adb::types;

namespace
{
    template <MessageComponentType type>
    struct component_by_type
    {
    };
    
    template <>
    struct component_by_type<MessageComponentType::ActionRow>
    {
        using Type = ActionRowValue;
    };

    /*template <>
    struct component_by_type<MessageComponentType::Button>
    {
        using Type = ButtonComponent;
    };

    template <>
    struct component_by_type<MessageComponentType::SelectMenu>
    {
        using Type = SelectMenuComponent;
    };*/

    template <>
    struct component_by_type<MessageComponentType::TextInput>
    {
        using Type = TextInputValue;
    };

    template<MessageComponentType type>
    std::shared_ptr<typename component_by_type<type>::Type> create()
    {
        auto *ptr = new component_by_type<type>::Type;
        return std::shared_ptr<typename component_by_type<type>::Type>(ptr);
    }
}

void adb::api::to_json(nlohmann::json& j, const std::shared_ptr<ComponentValueBase>& mc)
{
    switch (mc->type)
    {
        case MessageComponentType::ActionRow:
        {
            auto ptr = std::static_pointer_cast<component_by_type<MessageComponentType::ActionRow>::Type>(mc);
            j = *ptr;
            break;
        }
        case MessageComponentType::TextInput:
        {
            auto ptr = std::static_pointer_cast<component_by_type<MessageComponentType::TextInput>::Type>(mc);
            j = *ptr;
            break;
        }
        /*case MessageComponentType::Button:
        {
            auto ptr = std::static_pointer_cast<component_by_type<MessageComponentType::Button>::Type>(mc);
            j = *ptr;
            break;
        }
        case MessageComponentType::SelectMenu:
        {
            auto ptr = std::static_pointer_cast<component_by_type<MessageComponentType::SelectMenu>::Type>(mc);
            j = *ptr;
            break;
        }*/
    }
}

void adb::api::from_json(const nlohmann::json& j, std::shared_ptr<ComponentValueBase>& mc)
{
    MessageComponentType type;
    j.at("type").get_to(type);
    switch (type)
    {
        case MessageComponentType::ActionRow:
        {
            auto ptr = create<MessageComponentType::ActionRow>();
            j.get_to(*ptr);
            mc = ptr;
            break;
        }
        case MessageComponentType::TextInput:
        {
            auto ptr = std::make_shared<component_by_type<MessageComponentType::TextInput>::Type>();
            j.get_to(*ptr);
            mc = ptr;
            break;
        }
        /*case MessageComponentType::Button:
        {
            auto ptr = std::make_shared<component_by_type<MessageComponentType::Button>::Type>();
            j.get_to(*ptr);
            mc = ptr;
            break;
        }
        case MessageComponentType::SelectMenu:
        {
            auto ptr = std::make_shared<component_by_type<MessageComponentType::SelectMenu>::Type>();
            j.get_to(*ptr);
            mc = ptr;
            break;
        }*/
    }
}