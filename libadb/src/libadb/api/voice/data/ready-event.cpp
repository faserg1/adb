#include <libadb/api/voice/data/ready-event.hpp>
#include <nlohmann/json.hpp>

using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const VoiceReadyEvent& ready)
{
    j = nlohmann::json
    {
        {"ssrc", ready.ssrc},
        {"ip", ready.ip},
        {"port", ready.port},
        {"modes", ready.modes},
        {"heartbeat_interval", ready.heartbeatInterval}
    };
}

void adb::api::from_json(const nlohmann::json& j, VoiceReadyEvent& ready)
{
    j.at("ssrc").get_to(ready.ssrc);
    j.at("ip").get_to(ready.ip);
    j.at("port").get_to(ready.port);
    j.at("modes").get_to(ready.modes);
    if (j.contains("heartbeat_interval"))
        j.at("heartbeat_interval").get_to(ready.heartbeatInterval);
}