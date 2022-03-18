#include <libadb/api/interactions/data/application-command-permission.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ApplicationCommandPermission& permission)
{
    j = nlohmann::json
    {
        {"id", permission.id},
        {"type", permission.type},
        {"permission", permission.permission},
    };
}

void adb::api::from_json(const nlohmann::json& j, ApplicationCommandPermission& permission)
{
    j.at("id").get_to(permission.id);
    j.at("type").get_to(permission.type);
    j.at("permission").get_to(permission.permission);
}