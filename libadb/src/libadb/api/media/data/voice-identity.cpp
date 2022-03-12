#include <libadb/api/media/data/voice-identity.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const VoiceIdentity& identity)
{
    j = nlohmann::json
    {
        {"server_id", identity.serverId},
        {"user_id", identity.userId},
        {"session_id", identity.sessionId},
        {"token", identity.token},
    };
    map_to_json(j, "video", identity.video);
    map_to_json(j, "streams", identity.streams);
}

void adb::api::from_json(const nlohmann::json& j, VoiceIdentity& identity)
{
    j.at("server_id").get_to(identity.serverId);
    j.at("user_id").get_to(identity.userId);
    j.at("session_id").get_to(identity.sessionId);
    j.at("token").get_to(identity.token);
    map_from_json(j, "video", identity.video);
    map_from_json(j, "streams", identity.streams);
}