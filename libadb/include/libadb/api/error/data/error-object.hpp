#pragma once

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/api/error/data/error-object-suberror.hpp>

namespace adb::api
{
    struct ErrorObject
    {
        std::map<std::string, ErrorObject> subErrors;
        std::vector<ErrorObjectSubError> errors;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ErrorObject& errorObj);
    LIBADB_API void from_json(const nlohmann::json& j, ErrorObject& errorObj);
}