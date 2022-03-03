#pragma once

#include <string>
#include <cstddef>
#include <vector>
#include <span>

namespace adb::encoding
{
    std::string encode(std::span<std::byte> data);
    std::vector<std::byte> decode(const std::string &encodedData);
}