#include <api/voice/data/ip-discovery.hpp>
#include <type_traits>
#include <encoding/endian.hpp>
using namespace adb::api;

std::vector<std::byte> adb::api::toBytes(const IPDiscovery &ipDiscovery)
{
    std::vector<std::byte> bytes(74);
    std::byte *dstPtr = bytes.data();
    writeToBuffer(ipDiscovery.type, dstPtr);
    dstPtr += sizeof(ipDiscovery.type);
    writeToBuffer(ipDiscovery.length, dstPtr);
    dstPtr += sizeof(ipDiscovery.length);
    writeToBuffer(ipDiscovery.ssrc, dstPtr);
    dstPtr += sizeof(ipDiscovery.ssrc);
    return bytes;
}

IPDiscovery adb::api::fromBytes(const std::vector<std::byte> &bytes)
{
    IPDiscovery ipDiscovery;
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
    return ipDiscovery;
}