#pragma once

#include <string>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/api/error/data/error-code.hpp>
#include <libadb/api/error/data/error-object.hpp>


namespace adb::api
{
    struct Error
    {
        ErrorCode code;
        std::string message;
        std::map<std::string, ErrorObject> errors;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Error& error);
    LIBADB_API void from_json(const nlohmann::json& j, Error& error);
}