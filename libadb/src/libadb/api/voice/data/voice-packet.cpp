#include <libadb/api/voice/data/voice-packet.hpp>
#include <libadb/encoding/endian.hpp>
using namespace adb::api;

namespace
{
    constexpr const auto headerSize = 
        sizeof(VoicePacket::vpxcc) + sizeof(VoicePacket::mpt) + 
        sizeof(VoicePacket::sequnce) + sizeof(VoicePacket::timestamp) + sizeof(VoicePacket::ssrc);
}

std::vector<std::byte> adb::api::toBytes(const VoicePacket &packet)
{
    std::vector<std::byte> bytes(headerSize + packet.data.size());
    std::byte *dstPtr = bytes.data();
    *dstPtr = packet.vpxcc;
    dstPtr++;
    *dstPtr = packet.mpt;
    dstPtr++;
    writeToBuffer(packet.sequnce, dstPtr);
    dstPtr += sizeof(packet.sequnce);
    writeToBuffer(packet.timestamp, dstPtr);
    dstPtr += sizeof(packet.timestamp);
    writeToBuffer(packet.ssrc, dstPtr);
    dstPtr += sizeof(packet.ssrc);
    memcpy(dstPtr, packet.data.data(), packet.data.size());
    return bytes;
}

void adb::api::fromBytes(const std::vector<std::byte> &bytes, VoicePacket &packet)
{
    packet.data.resize(bytes.size() - headerSize);
    const std::byte *srcPtr = bytes.data();
    packet.vpxcc = *srcPtr;
    srcPtr++;
    packet.mpt = *srcPtr;
    srcPtr++;
    readFromBuffer(packet.sequnce, srcPtr);
    srcPtr += sizeof(packet.sequnce);
    readFromBuffer(packet.timestamp, srcPtr);
    srcPtr += sizeof(packet.timestamp);
    readFromBuffer(packet.ssrc, srcPtr);
    srcPtr += sizeof(packet.ssrc);
    memcpy(packet.data.data(), srcPtr, packet.data.size());
}