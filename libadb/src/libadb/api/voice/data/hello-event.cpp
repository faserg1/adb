#include <libadb/api/voice/data/hello-event.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const VoiceHelloEvent& hello)
{
    j = nlohmann::json
    {
        {"heartbeat_interval", hello.heartbeatInterval},
        {"v", hello.version}
    };
}

void adb::api::from_json(const nlohmann::json& j, VoiceHelloEvent& hello)
{
    j.at("heartbeat_interval").get_to(hello.heartbeatInterval);
    map_from_json(j, "v", hello.version);
}