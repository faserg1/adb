#include <libadb/api/error/data/error-object.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const ErrorObject& errorObj)
{
    if (!errorObj.errors.empty())
        j["_errors"] = errorObj.errors;
    else
        j = errorObj.subErrors;
}

void adb::api::from_json(const nlohmann::json& j, ErrorObject& errorObj)
{
    if (j.contains("_errors"))
        j.at("_errors").get_to(errorObj.errors);
    else
        j.get_to(errorObj.subErrors);
}