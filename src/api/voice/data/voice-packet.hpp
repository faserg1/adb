#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

namespace adb::api
{
    struct VoicePacket
    {
        std::byte versionFlags;
        std::byte payloadType;
        uint16_t sequnce;
        uint16_t timestamp;
        
    };
}