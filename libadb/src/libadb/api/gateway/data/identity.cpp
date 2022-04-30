#include <libadb/api/gateway/data/identity.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

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
    map_to_json(j, "compress", identity.compress);
    map_to_json(j, "large_threshold", identity.largeThresgold);
    map_to_json(j, "shard", identity.shard);
}

void adb::api::from_json(const nlohmann::json& j, Identity& identity)
{
    j.at("token").get_to(identity.token);
    j.at("properties").get_to(identity.properties);
    j.at("tokintentsen").get_to(identity.intents);
    map_from_json(j, "compress", identity.compress);
    map_from_json(j, "large_threshold", identity.largeThresgold);
    map_from_json(j, "shard", identity.shard);
}