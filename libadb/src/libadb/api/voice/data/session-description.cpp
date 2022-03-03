#include <libadb/api/voice/data/session-description.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const SessionDescription& desc)
{
    j = nlohmann::json
    {
        {"mode", desc.mode},
        {"secret_key", desc.secretKey}
    };
}

void adb::api::from_json(const nlohmann::json& j, SessionDescription& desc)
{
    j.at("mode").get_to(desc.mode);
    j.at("secret_key").get_to(desc.secretKey);
}