#include <libadb/api/media/data/ip-discovery.hpp>
#include <libadb/encoding/endian.hpp>
using namespace adb::api;

std::vector<std::byte> adb::api::toBytes(const IPDiscovery &ipDiscovery)
{
    constexpr const auto dataSize = 
        sizeof(IPDiscovery::type) + sizeof(IPDiscovery::length) + sizeof(IPDiscovery::ssrc) +
        sizeof(IPDiscovery::address) + sizeof(IPDiscovery::port);
    std::vector<std::byte> bytes(dataSize);
    std::byte *dstPtr = bytes.data();
    writeToBuffer(ipDiscovery.type, dstPtr);
    dstPtr += sizeof(ipDiscovery.type);
    writeToBuffer(ipDiscovery.length, dstPtr);
    dstPtr += sizeof(ipDiscovery.length);
    writeToBuffer(ipDiscovery.ssrc, dstPtr);
    dstPtr += sizeof(ipDiscovery.ssrc);
    return bytes;
}

void adb::api::fromBytes(const std::vector<std::byte> &bytes, IPDiscovery &ipDiscovery)
{
    const std::byte *srcPtr = bytes.data();
    auto readFunc = [&srcPtr](auto &what)
    {
        memcpy(&what, srcPtr, sizeof(what));
        srcPtr += sizeof(what);
    };
    readFromBuffer(ipDiscovery.type, srcPtr);
    srcPtr += sizeof(ipDiscovery.type);
    readFromBuffer(ipDiscovery.length, srcPtr);
    srcPtr += sizeof(ipDiscovery.length);
    readFromBuffer(ipDiscovery.ssrc, srcPtr);
    srcPtr += sizeof(ipDiscovery.ssrc);
    readFunc(ipDiscovery.address);
    readFromBuffer(ipDiscovery.port, srcPtr);
}