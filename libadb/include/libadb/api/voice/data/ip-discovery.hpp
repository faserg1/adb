#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

namespace adb::api
{
    enum class IPDiscoveryType : uint16_t
    {
        Request = 0x1,
        Response = 0x2
    };

    /**
     * @brief 
     * @https://discord.com/developers/docs/topics/voice-connections#ip-discovery 
     */
    struct IPDiscovery final
    {
        /// Values 0x1 and 0x2 indicate request and response, respectively
        IPDiscoveryType type;
        /// Message length excluding Type and Length fields (value 70)
        uint16_t length = 70;
        /// Unsigned integer (SSRC from ready event)
        uint32_t ssrc;
        /// Null-terminated string in response
        char address[64] = {0};
        /// Unsigned short
        uint16_t port = 0;
    };

    std::vector<std::byte> toBytes(const IPDiscovery &ipDiscovery);
    void fromBytes(const std::vector<std::byte> &bytes, IPDiscovery &ipDiscovery);
}