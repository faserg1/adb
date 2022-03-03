#pragma once

#include <bit>
#include <cstring>
#include <concepts>

template <std::integral Number>
void writeToBuffer(Number num, std::byte *dst)
{
    if constexpr (std::endian::native == std::endian::big)
        std::memcpy(dst, &num, sizeof(Number));
    else
    {
        for (size_t byteNumber = 0; byteNumber < sizeof(Number); byteNumber++)
        {
            dst[byteNumber] = (std::byte) ((num >> ((sizeof(Number) - (byteNumber + 1)) * 8)) & 0xff);
        }
    }
}

template <class Enum>
requires std::is_enum_v<Enum>
void writeToBuffer(Enum value, std::byte *dst)
{
    writeToBuffer(static_cast<std::underlying_type_t<Enum>>(value), dst);
}

template <std::integral Number>
void readFromBuffer(Number &num, const std::byte *src)
{
    if constexpr (std::endian::native == std::endian::big)
        std::memcpy(&num, src, sizeof(Number));
    else
    {
        num = 0x0;
        for (size_t byteNumber = 0; byteNumber < sizeof(Number); byteNumber++)
        {
            Number temp = (Number) src[byteNumber];
            num |= temp << ((sizeof(Number) - (byteNumber + 1)) * 8);
        }
    }
}

template <class Enum>
requires std::is_enum_v<Enum>
void readFromBuffer(Enum &value, const std::byte *src)
{
    readFromBuffer(*reinterpret_cast<std::add_pointer_t<std::underlying_type_t<Enum>>>(&value), src);
}