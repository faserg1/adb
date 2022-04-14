#pragma once

#include <string>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    struct ErrorObjectSubError
    {
        std::string code;
        std::string message;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ErrorObjectSubError& subError);
    LIBADB_API void from_json(const nlohmann::json& j, ErrorObjectSubError& subError);
}