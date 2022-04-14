#include <libadb/api/error/data/error.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Error& error)
{
    j = nlohmann::json
    {
        {"code", error.code},
        {"message", error.message},
    };
    if (error.errors.empty())
        j["errors"] = error.errors;
}

void adb::api::from_json(const nlohmann::json& j, Error& error)
{
    j.at("code").get_to(error.code);
    j.at("message").get_to(error.message);
    if (j.contains("errors"))
        j.at("errors").get_to(error.errors);
}