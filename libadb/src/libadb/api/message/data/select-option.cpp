#include <libadb/api/message/data/select-option.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const SelectOption& op)
{
    j =
    {
        {"label", op.label},
        {"value", op.value}
    };
    map_to_json(j, "description", op.description);
    map_to_json(j, "emoji", op.emoji);
    map_to_json(j, "default", op.isDefault);
}

void adb::api::from_json(const nlohmann::json& j, SelectOption& op)
{
    j.at("label").get_to(op.label);
    j.at("value").get_to(op.label);
    map_from_json(j, "description", op.description);
    map_from_json(j, "emoji", op.emoji);
    map_from_json(j, "default", op.isDefault);
}
