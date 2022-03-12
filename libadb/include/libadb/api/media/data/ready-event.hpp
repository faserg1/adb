#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>
#include <libadb/libadb.hpp>

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

    LIBADB_API void to_json(nlohmann::json& j, const VoiceReadyEvent& ready);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceReadyEvent& ready);
}