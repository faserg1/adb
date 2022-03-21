#include <libadb/api/interactions/data/modal.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Modal& modal)
{
    j = nlohmann::json
    {
        {"custom_id", modal.customId},
        {"title", modal.title},
        {"components", modal.components}
    };
}

void adb::api::from_json(const nlohmann::json& j, Modal& modal)
{
    j.at("custom_id").get_to(modal.customId);
    j.at("title").get_to(modal.title);
    j.at("components").get_to(modal.components);
}