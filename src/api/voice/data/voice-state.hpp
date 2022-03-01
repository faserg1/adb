#pragma once

#include <types/snowflake.hpp>
#include <types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>
#include <api/guild/data/guild-member.hpp>
#include <types/time.hpp>

namespace adb::api
{
    struct VoiceState
    {
        /// the guild id this voice state is for
        std::optional<adb::types::SFID> guildId;
        /// the channel id this user is connected to
        std::optional<adb::types::SFID> channelId;
        /// the user id this voice state is for
        adb::types::SFID userId;
        /// the guild member this voice state is for
        std::optional<GuildMember> member;
        /// the session id for this voice state
        std::string sessionId;
        /// whether this user is deafened by the server
        bool deaf;
        /// whether this user is muted by the server
        bool mute;
        /// whether this user is locally muted
        bool selfMute;
        /// whether this user is locally deafened
        bool selfDeaf;
        /// whether this user is streaming using "Go Live"
        std::optional<bool> selfStream;
        /// whether this user's camera is enabled
        bool selfVideo;
        /// whether this user is muted by the current user
        bool suppress;
        /// the time at which the user requested to speak
        adb::types::Nullable<adb::types::TimePoint> requestToSpeakTimestamp;
    };

    void to_json(nlohmann::json& j, const VoiceState& voiceState);
    void from_json(const nlohmann::json& j, VoiceState& voiceState);
}