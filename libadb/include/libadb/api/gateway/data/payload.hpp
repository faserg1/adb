#pragma once

#include <string>
#include <cstdint>
#include <optional>
#include <nlohmann/json.hpp>
#include <libadb/libadb.hpp>
#include <libadb/api/gateway/data/opcode.hpp>

namespace adb::api
{
    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/gateway#payloads-gateway-payload-structure
     */
    struct Payload
    {
        GatewayOpCode op;
        nlohmann::json data;
        std::optional<uint64_t> sequence;
        std::optional<std::string> eventName;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Payload& payload);
    LIBADB_API void from_json(const nlohmann::json& j, Payload& payload);
}