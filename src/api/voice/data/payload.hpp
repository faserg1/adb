#pragma once

#include <api/voice/data/opcode.hpp>
#include <nlohmann/json.hpp>

namespace adb::api
{
    struct VoicePayload
    {
        VoiceOpCode opCode;
        nlohmann::json data;
    };

    void to_json(nlohmann::json& j, const VoicePayload& payload);
    void from_json(const nlohmann::json& j, VoicePayload& payload);
}