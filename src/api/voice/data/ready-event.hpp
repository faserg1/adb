#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>

namespace adb::api
{
    /**
     * @brief Voice Ready Event
     * @details https://discord.com/developers/docs/topics/voice-connections#establishing-a-voice-websocket-connection-example-voice-ready-payload
     */
    struct VoiceReadyEvent
    {
        uint32_t ssrc;
        std::string ip;
        uint32_t port;
        std::vector<std::string> modes;
        /// should be ignored
        uint64_t heartbeatInterval;
    };

    void to_json(nlohmann::json& j, const VoiceReadyEvent& ready);
    void from_json(const nlohmann::json& j, VoiceReadyEvent& ready);
}