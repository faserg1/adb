#include <libadb/api/voice/data/payload.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const VoicePayload& payload)
{
    j = nlohmann::json
    {
        {"op", payload.opCode},
        {"d", payload.data}
    };
}

void adb::api::from_json(const nlohmann::json& j, VoicePayload& payload)
{
    j.at("op").get_to(payload.opCode);
    if (j.contains("d") && !j.at("d").is_null())
        j.at("d").get_to(payload.data);
}