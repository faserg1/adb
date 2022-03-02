#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>

namespace adb::api
{
    struct VoiceReadyEvent
    {
        uint64_t ssrc;
        std::string ip;
        uint32_t port;
        std::vector<std::string> modes;
        /// should be ignored
        uint64_t heartbeatInterval;
    };

    void to_json(nlohmann::json& j, const VoiceReadyEvent& ready);
    void from_json(const nlohmann::json& j, VoiceReadyEvent& ready);
}