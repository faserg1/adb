#include <libadb/api/gateway/data/identity.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const IdentityConnectionProperties& prop)
{
    j = nlohmann::json
    {
        {"$os", prop.os},
        {"$browser", prop.browser},
        {"$device", prop.device}
    };
}

void adb::api::from_json(const nlohmann::json& j, IdentityConnectionProperties& prop)
{
    j.at("$os").get_to(prop.os);
    j.at("$browser").get_to(prop.browser);
    j.at("$device").get_to(prop.device);
}

void adb::api::to_json(nlohmann::json& j, const Identity& identity)
{
    j = nlohmann::json
    {
        {"token", identity.token},
        {"properties", identity.properties},
        {"intents", identity.intents}
    };
}

void adb::api::from_json(const nlohmann::json& j, Identity& identity)
{
    j.at("token").get_to(identity.token);
    j.at("properties").get_to(identity.properties);
    j.at("tokintentsen").get_to(identity.intents);
}