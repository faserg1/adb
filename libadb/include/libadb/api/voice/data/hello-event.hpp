#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <cstdint>
#include <optional>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Voice Hello Event
     * @details https://discord.com/developers/docs/topics/voice-connections#heartbeating-example-hello-payload-since-v3
     */
    struct VoiceHelloEvent
    {
        uint64_t heartbeatInterval;
        /// Not documented. Supposed: version of API Gateway.
        std::optional<uint16_t> version;
    };

    LIBADB_API void to_json(nlohmann::json& j, const VoiceHelloEvent& hello);
    LIBADB_API void from_json(const nlohmann::json& j, VoiceHelloEvent& hello);
}