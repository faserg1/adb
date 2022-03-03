#include <libadb/api/gateway/data/hello.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Hello& hello)
{
    j = nlohmann::json {
        {"heartbeat_interval", hello.heartbeatInterval}
    };
}

void adb::api::from_json(const nlohmann::json& j, Hello& hello)
{
    j.at("heartbeat_interval").get_to(hello.heartbeatInterval);
}