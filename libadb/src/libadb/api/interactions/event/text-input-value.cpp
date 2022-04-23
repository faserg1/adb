#include <libadb/api/interactions/event/text-input-value.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const TextInputValue& textInput)
{
    j = nlohmann::json
    {
        {"type", MessageComponentType::TextInput},
        {"custom_id", textInput.customId},
    };
    map_to_json(j, "value", textInput.value);
}

void adb::api::from_json(const nlohmann::json& j, TextInputValue& textInput)
{
    j.at("type").get_to(textInput.type);
    j.at("custom_id").get_to(textInput.customId);
    map_from_json(j, "value", textInput.value);
}
