#include <libadb/api/utils/read-response.hpp>
#include <libadb/api/error/check-endpoint-error.hpp>
using namespace adb::api;

// TODO: HTTP ERROR

bool adb::api::readCommandResponse(const cpr::Response &response)
{
    if (response.text.empty())
        return response.status_code >= 200 && response.status_code < 300;
    if (!response.header.contains("Content-Type"))
        return false;
    if (response.header.at("Content-Type") != "application/json")
        return false;
    auto jresponse = nlohmann::json::parse(response.text);
    if (checkEndpointError(jresponse))
        return false;
    // ???
    return false;
}

std::optional<nlohmann::json> adb::api::readRequestResponseJson(const cpr::Response &response)
{
    if (!response.header.contains("Content-Type"))
        return {};
    if (response.header.at("Content-Type") != "application/json")
        return {};
    auto jresponse = nlohmann::json::parse(response.text);
    if (!checkEndpointError(jresponse))
        return jresponse;
    return {};
}