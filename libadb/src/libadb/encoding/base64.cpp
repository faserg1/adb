#include <libadb/encoding/base64.hpp>
#include <algorithm>
#include <execution>
#include <ranges>
#include <libadb/types/helpers/ranges/range.hpp>

namespace
{
    constexpr std::string_view eTable{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
    constexpr uint8_t toByte(char a)
    {
        if (a >= 'A' && a <= 'Z')
            return uint8_t{0} + (uint8_t) (a - 'A');
        if (a >= 'a' && a <= 'z')
            return uint8_t{26} + (uint8_t) (a - 'a');
        if (a >= '0' && a <= '9')
            return uint8_t{52} + (uint8_t) (a - '0');
        if (a == '+')
            return 62;
        if (a == '/')
            return 63;
        if (a == '=')
            return 0;
        throw a;
    }
}

std::string adb::encoding::encode(std::span<std::byte> data)
{
    const auto totalBits = data.size() * 8;
    const auto needSize = (totalBits / 6);
    const auto totalPadding = (4 - (needSize % 4)) - 1;
    std::string encodedData;
    encodedData.resize(needSize + totalPadding + 1);
    const auto* dt = reinterpret_cast<const uint8_t*>(data.data());
    auto rng = adb::types::Range<int64_t>(0, needSize/4);
    std::for_each(std::execution::par_unseq, rng.begin(), rng.end(), [dt, &encodedData](auto blockIdx)
    {
        const auto dIdx = blockIdx * 3;
        const auto eIdx = blockIdx * 4;

        auto a = (dt[dIdx + 0] >> 2) & uint8_t{0b00111111};
        auto b = ((dt[dIdx + 0] << 4) & uint8_t{0b00110000}) | ((dt[dIdx + 1] >> 4) & uint8_t{0b00001111});
        auto c = ((dt[dIdx + 1] << 2) & uint8_t{0b00111100}) | ((dt[dIdx + 2] >> 6) & uint8_t{0b00000011});
        auto d = dt[dIdx + 2] & uint8_t{0b00111111};
        encodedData[eIdx + 0] = eTable[a];
        encodedData[eIdx + 1] = eTable[b];
        encodedData[eIdx + 2] = eTable[c];
        encodedData[eIdx + 3] = eTable[d];
    });
    if (totalPadding > 0)
    {
        const auto dIdx = (needSize/4) * 3;
        const auto eIdx = (needSize/4) * 4;

        const auto dA = dt[dIdx + 0];
        const auto dB = totalPadding == 2 ? 0 : dt[dIdx + 1];
        const auto dC = totalPadding >= 1 ? 0 : dt[dIdx + 2];

        auto a = (dA >> 2) & uint8_t{0b00111111};
        auto b = ((dA << 4) & uint8_t{0b00110000}) | ((dB >> 4) & uint8_t{0b00001111});
        auto c = ((dB << 2) & uint8_t{0b00111100}) | ((dC >> 6) & uint8_t{0b00000011});
        auto d = dC & uint8_t{0b00111111};
        encodedData[eIdx + 0] = eTable[a];
        encodedData[eIdx + 1] = eTable[b];
        encodedData[eIdx + 2] = totalPadding == 2 ? '=' : eTable[c];
        encodedData[eIdx + 3] = totalPadding >= 1 ? '=' : eTable[d];
    }
    return std::move(encodedData);
}

std::vector<std::byte> adb::encoding::decode(const std::string &encodedData)
{
    const auto blocks = encodedData.size() / 4;
    const auto padding = (encodedData[encodedData.size() - 2] == '=') ? 2 :
        (encodedData[encodedData.size() - 1] == '=' ? 1 : 0);
    auto rng = adb::types::Range<int64_t>(0, blocks - (padding ? 1 : 0));
    std::vector<std::byte> total(blocks*3 - padding);
    auto* dt = reinterpret_cast<uint8_t*>(total.data());
    std::for_each(std::execution::par_unseq, rng.begin(), rng.end(), [dt, &encodedData](auto blockIdx)
    {
        const auto dIdx = blockIdx * 3;
        const auto eIdx = blockIdx * 4;

        const auto eA = toByte(encodedData[eIdx + 0]);
        const auto eB = toByte(encodedData[eIdx + 1]);
        const auto eC = toByte(encodedData[eIdx + 2]);
        const auto eD = toByte(encodedData[eIdx + 3]);

        dt[dIdx + 0] = (eA << 2) | ((eB >> 4) & 0b00000011);
        dt[dIdx + 1] = ((eB << 4) & 0b11110000) | ((eC >> 2) & 0b00001111);
        dt[dIdx + 2] = ((eC << 6) & 0b11000000) | (eD & 0b00111111);
    });
    if (padding)
    {
        const auto blockIdx = blocks-1;
        const auto dIdx = blockIdx * 3;
        const auto eIdx = blockIdx * 4;

        const auto eA = toByte(encodedData[eIdx + 0]);
        const auto eB = toByte(encodedData[eIdx + 1]);
        const auto eC = toByte(encodedData[eIdx + 2]);
        const auto eD = toByte(encodedData[eIdx + 3]);

        auto addonIdx = 0;
        dt[dIdx + addonIdx++] = (eA << 2) | ((eB >> 4) & 0b00000011);
        if (padding == 1)
            dt[dIdx + addonIdx++] = ((eB << 4) & 0b11110000) | ((eC >> 2) & 0b00001111);
    }
    return std::move(total);
}