#include <libadb/api/error/data/error-object-suberror.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const ErrorObjectSubError& subError)
{
    j = nlohmann::json
    {
        {"code", subError.code},
        {"message", subError.message}
    };
}

void adb::api::from_json(const nlohmann::json& j, ErrorObjectSubError& subError)
{
    j.at("code").get_to(subError.code);
    j.at("message").get_to(subError.message);
}