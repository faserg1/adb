#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <libadb/api/message/data/send-message.hpp>

namespace adb::api
{
    using AdditionalHeaders = std::vector<std::pair<std::string, std::string>>;

    void fillSessionWithMessage(const SendMessageParams &params, const std::string &data, cpr::Session &session, AdditionalHeaders headers);
}