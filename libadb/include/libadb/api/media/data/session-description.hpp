#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    struct SessionDescription
    {
        std::string mode;
        std::vector<std::byte> secretKey;
    };

    LIBADB_API void to_json(nlohmann::json& j, const SessionDescription& desc);
    LIBADB_API void from_json(const nlohmann::json& j, SessionDescription& desc);
}