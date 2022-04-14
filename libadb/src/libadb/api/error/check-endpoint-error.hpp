#pragma once

#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    bool checkEndpointError(const nlohmann::json &errorMsg);
}