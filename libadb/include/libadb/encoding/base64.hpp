#pragma once

#include <string>
#include <cstddef>
#include <vector>
#include <span>
#include <libadb/libadb.hpp>

namespace adb::encoding
{
    LIBADB_API std::string encode(std::span<std::byte> data);
    LIBADB_API std::vector<std::byte> decode(const std::string &encodedData);
}