#include <api/voice/data/voice-state-update.hpp>
#include <nlohmann/json.hpp>
#include <types/helpers/json-nullable.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const VoiceStateUpdate& stateUpdate)
{
    j = nlohmann::json
    {
        {"guild_id", stateUpdate.guildId},
        {"channel_id", stateUpdate.channelId},
        {"self_mute", stateUpdate.selfMute},
        {"self_deaf", stateUpdate.selfDeaf},
    };
}

void adb::api::from_json(const nlohmann::json& j, VoiceStateUpdate& stateUpdate)
{
    // TODO? 
}