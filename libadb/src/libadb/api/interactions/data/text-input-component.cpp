#include <libadb/api/interactions/data/text-input-component.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const TextInputComponent& textInput)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::TextInput},
        {"custom_id", textInput.customId},
        {"style", textInput.style},
        {"label", textInput.label},
    };
    map_to_json(j, "min_length", textInput.minLength);
    map_to_json(j, "max_length", textInput.maxLength);
    map_to_json(j, "required", textInput.required);
    map_to_json(j, "value", textInput.value);
    map_to_json(j, "placeholder", textInput.placeholder);
}

void adb::api::from_json(const nlohmann::json& j, TextInputComponent& textInput)
{
    j.at("type").get_to(textInput.type);
    j.at("custom_id").get_to(textInput.customId);
    j.at("style").get_to(textInput.style);
    j.at("label").get_to(textInput.label);
    map_from_json(j, "min_length", textInput.minLength);
    map_from_json(j, "max_length", textInput.maxLength);
    map_from_json(j, "required", textInput.required);
    map_from_json(j, "value", textInput.value);
    map_from_json(j, "placeholder", textInput.placeholder);
}

MessageComponent adb::api::createTextInput(const TextInputComponent &ti)
{
    auto ptr = std::make_shared<TextInputComponent>(ti);
    ptr->type = MessageComponentType::TextInput;
    return ptr;
}