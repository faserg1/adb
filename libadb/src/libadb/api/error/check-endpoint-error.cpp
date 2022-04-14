#include <libadb/api/error/check-endpoint-error.hpp>
#include <libadb/api/error/endpoint-error.hpp>
#include <nlohmann/json.hpp>

bool adb::api::checkEndpointError(const nlohmann::json &errorMsg)
{
    if (errorMsg.contains("code") && errorMsg.contains("message"))
    {
        throw adb::api::EndpointError(errorMsg.get<adb::api::Error>());
        return true;
    }
    return false;
}