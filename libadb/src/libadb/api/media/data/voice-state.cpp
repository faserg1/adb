#include <libadb/api/media/data/voice-state.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-optional.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const VoiceState& voiceState)
{
    j = nlohmann::json {};
    map_to_json(j, "guild_id", voiceState.guildId);
    map_to_json(j, "channel_id", voiceState.channelId);
    j["user_id"] = voiceState.userId;
    map_to_json(j, "member", voiceState.member);
    j["session_id"] = voiceState.sessionId;
    j["deaf"] = voiceState.deaf;
    j["mute"] = voiceState.mute;
    j["self_mute"] = voiceState.selfMute;
    j["self_deaf"] = voiceState.sessionId;
    map_to_json(j, "self_stream", voiceState.selfStream);
    j["self_video"] = voiceState.selfVideo;
    j["suppress"] = voiceState.suppress;
    map_to_json(j, "request_to_speak_timestamp", voiceState.requestToSpeakTimestamp);
}

void adb::api::from_json(const nlohmann::json& j, VoiceState& voiceState)
{
    map_from_json(j, "guild_id", voiceState.guildId);
    map_from_json(j, "channel_id", voiceState.channelId);
    j.at("user_id").get_to(voiceState.userId);
    map_from_json(j, "member", voiceState.member);
    j.at("session_id").get_to(voiceState.sessionId);
    j.at("deaf").get_to(voiceState.deaf);
    j.at("mute").get_to(voiceState.mute);
    j.at("self_mute").get_to(voiceState.selfMute);
    j.at("self_deaf").get_to(voiceState.selfDeaf);
    map_from_json(j, "self_stream", voiceState.selfStream);
    j.at("self_video").get_to(voiceState.selfVideo);
    j.at("suppress").get_to(voiceState.suppress);
    map_from_json(j, "request_to_speak_timestamp", voiceState.requestToSpeakTimestamp);
}