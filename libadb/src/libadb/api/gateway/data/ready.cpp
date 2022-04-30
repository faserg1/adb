#include <libadb/api/gateway/data/ready.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Ready& ready)
{
    j = nlohmann::json
    {
        { "v", ready.v },
        { "user", ready.user },
        { "guilds", ready.guilds },
        { "session_id", ready.sessionId },
        { "application", nlohmann::json
            {
                { "id", ready.application.id },
                { "flags", ready.application.flags },
            }
        },
    };
    map_to_json(j, "shard", ready.shard);
}

void adb::api::from_json(const nlohmann::json& j, Ready& ready)
{
    j.at("v").get_to(ready.v);
    j.at("user").get_to(ready.user);
    j.at("guilds").get_to(ready.guilds);
    j.at("session_id").get_to(ready.sessionId);
    j.at("application").at("id").get_to(ready.application.id);
    j.at("application").at("flags").get_to(ready.application.flags);
    map_from_json(j, "shard", ready.shard);
}