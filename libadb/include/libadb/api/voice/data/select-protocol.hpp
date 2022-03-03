#pragma once

#include <string>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Select Protocol Payload
     * @details https://discord.com/developers/docs/topics/voice-connections#establishing-a-voice-udp-connection-example-select-protocol-payload
     */
    struct SelectProtocol
    {
        std::string protocol;
        struct SelectProtocolData
        {
            std::string address;
            uint16_t port;
            std::string mode;
        } data;
    };

    void to_json(nlohmann::json& j, const SelectProtocol& selectProtocol);
    void from_json(const nlohmann::json& j, SelectProtocol& selectProtocol);
}