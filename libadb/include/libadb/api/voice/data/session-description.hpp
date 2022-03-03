#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    struct SessionDescription
    {
        std::string mode;
        std::vector<std::byte> secretKey;
    };

    void to_json(nlohmann::json& j, const SessionDescription& desc);
    void from_json(const nlohmann::json& j, SessionDescription& desc);
}