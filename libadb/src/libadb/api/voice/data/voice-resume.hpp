#include <libadb/api/voice/data/voice-resume.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const VoiceResume& resume)
{
    j = nlohmann::json
    {
        {"server_id", resume.serverId},
        {"session_id", resume.sessionId},
        {"token", resume.token},
    };
}

void adb::api::from_json(const nlohmann::json& j, VoiceResume& identity)
{
    j.at("server_id").get_to(resume.serverId);
    j.at("session_id").get_to(resume.sessionId);
    j.at("token").get_to(resume.token);
}