#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <libadb/api/message/data/create-message.hpp>
#include <libadb/api/message/data/edit-message.hpp>

namespace adb::api
{
    using AdditionalHeaders = std::vector<std::pair<std::string, std::string>>;

    void fillSessionWithMessage(const CreateMessageParams &params, const std::string &data, cpr::Session &session, AdditionalHeaders headers);
    void fillSessionWithMessage(const EditMessageParams &params, const std::string &data, cpr::Session &session, AdditionalHeaders headers);
}