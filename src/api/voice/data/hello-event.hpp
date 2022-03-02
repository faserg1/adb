#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>

namespace adb::api
{
    struct VoiceHelloEvent
    {
        uint64_t heartbeatInterval;
    };

    void to_json(nlohmann::json& j, const VoiceHelloEvent& hello);
    void from_json(const nlohmann::json& j, VoiceHelloEvent& hello);
}