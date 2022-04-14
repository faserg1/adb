#pragma once

#include <optional>
#include <cpr/response.h>
#include <nlohmann/json.hpp>

namespace adb::api
{
    bool readCommandResponse(const cpr::Response &response);
    std::optional<nlohmann::json> readRequestResponseJson(const cpr::Response &response);
    template<class ReturnType>
    std::optional<ReturnType> readRequestResponseOpt(const cpr::Response &response)
    {
        if (auto data = readRequestResponseJson(response); data.has_value())
        {
            return data.value().get<ReturnType>();
        }
        return {};
    }
    template<class ReturnType>
    ReturnType readRequestResponse(const cpr::Response &response)
    {
        if (auto data = readRequestResponseJson(response); data.has_value())
        {
            return data.value().get<ReturnType>();
        }
        return {};
    }
}