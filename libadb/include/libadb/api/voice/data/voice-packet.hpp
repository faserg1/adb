#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Voice Packet, that can be received and sended to Voice UDP Data Channel
     * @details https://discord.com/developers/docs/topics/voice-connections#encrypting-and-sending-voice
     * @see https://github.com/discord/discord-api-docs/issues/365
     */
    struct VoicePacket
    {
        union 
        {
            struct {
                std::byte version : 2;
                std::byte padding : 1;
                std::byte extension : 1;
                std::byte CRSCcount : 4;
            };
            std::byte vpxcc;
        };
        union
        {
            struct {
                std::byte marker : 1;
                std::byte payloadType : 7;
            };
            std::byte mpt;
        };
        
        uint16_t sequnce;
        uint16_t timestamp;
        uint32_t ssrc;
        /// Binary data, encoded via opus and encrypted via sodium
        std::vector<std::byte> data;
    };

    LIBADB_API std::vector<std::byte> toBytes(const VoicePacket &packet);
    LIBADB_API void fromBytes(const std::vector<std::byte> &bytes, VoicePacket &packet);
}
