#include <libadb/api/voice/data/speaking.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>

using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const SpeakingSendPayload& speaking)
{
    j = nlohmann::json
    {
        {"speaking", speaking.speaking},
        {"delay", speaking.delay},
        {"ssrc", speaking.ssrc}
    };
}

void adb::api::from_json(const nlohmann::json& j, SpeakingSendPayload& speaking)
{
    j.at("speaking").get_to(speaking.speaking);
    j.at("delay").get_to(speaking.delay);
    j.at("ssrc").get_to(speaking.ssrc);
}

void adb::api::to_json(nlohmann::json& j, const SpeakingReceivePayload& speaking)
{
    j = nlohmann::json
    {
        {"speaking", speaking.speaking},
        {"user_id", speaking.userId},
        {"ssrc", speaking.ssrc}
    };
}

void adb::api::from_json(const nlohmann::json& j, SpeakingReceivePayload& speaking)
{
    j.at("speaking").get_to(speaking.speaking);
    j.at("user_id").get_to(speaking.userId);
    j.at("ssrc").get_to(speaking.ssrc);
}