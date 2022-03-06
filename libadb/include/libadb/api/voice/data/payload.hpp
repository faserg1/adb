#pragma once

#include <libadb/api/voice/data/opcode.hpp>
#include <nlohmann/json.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    struct VoicePayload
    {
        VoiceOpCode opCode;
        nlohmann::json data;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoicePayload& payload);
    LIBADB_API void from_json(const nlohmann::json& j, VoicePayload& payload);
}