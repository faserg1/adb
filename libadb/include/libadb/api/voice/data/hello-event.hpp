#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>
#include <libadb/libadb.hpp>

namespace adb::api
{
    struct VoiceHelloEvent
    {
        uint64_t heartbeatInterval;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceHelloEvent& hello);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceHelloEvent& hello);
}