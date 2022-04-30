#include <libadb/api/gateway/data/resume.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Resume& resume)
{
    j = nlohmann::json
    {
        { "token", resume.token },
        { "session_id", resume.sessionId },
        { "seq", resume.seq },
    };
}

void adb::api::from_json(const nlohmann::json& j, Resume& resume)
{
    j.at("token").get_to(resume.token);
    j.at("session_id").get_to(resume.sessionId);
    j.at("seq").get_to(resume.seq);
}