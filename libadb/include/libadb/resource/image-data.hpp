#pragma once

#include <libadb/libadb.hpp>
#include <libadb/resource/image-format.hpp>
#include <vector>
#include <cstdlib>
#include <nlohmann/json_fwd.hpp>

namespace adb::resource
{
    struct ImageData
    {
        ImageFormat format;
        std::vector<std::byte> data;
    };

    LIBADB_API std::string to_string(const ImageData &data);
    LIBADB_API void from_string(const std::string &input, ImageData &data);
    LIBADB_API void to_json(nlohmann::json& j, const ImageData& data);
    LIBADB_API void from_json(const nlohmann::json& j, ImageData& data);
}