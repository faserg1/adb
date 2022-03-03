#include <libadb/api/voice/data/voice-server-update-event.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const VoiceServerUpdateEvent& serverUpdateEvent)
{
    j = nlohmann::json
    {
        {"token", serverUpdateEvent.token},
        {"guild_id", serverUpdateEvent.guildId},
        {"endpoint", serverUpdateEvent.endpoint}
    };
}

void adb::api::from_json(const nlohmann::json& j, VoiceServerUpdateEvent& serverUpdateEvent)
{
    j.at("token").get_to(serverUpdateEvent.token);
    j.at("guild_id").get_to(serverUpdateEvent.guildId);
    j.at("endpoint").get_to(serverUpdateEvent.endpoint);
}