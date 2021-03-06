#include <libadb/api/error/check-endpoint-error.hpp>
#include <libadb/api/error/endpoint-error.hpp>
#include <nlohmann/json.hpp>
#include <loguru/loguru.hpp>

bool adb::api::checkEndpointError(const nlohmann::json &errorMsg)
{
    if (errorMsg.contains("code") && errorMsg.contains("message"))
    {
        const auto error = errorMsg.get<adb::api::Error>();
        LOG_F(ERROR, "Code: {}, Message: \"{}\"",  static_cast<uint64_t>(error.code), error.message);
        throw adb::api::EndpointError(error);
        return true;
    }
    return false;
}