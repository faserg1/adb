#include "send-message-session.hpp"
#include <fmt/core.h>
#include <algorithm>
using namespace adb::api;

void adb::api::fillSessionWithMessage(const SendMessageParams &params, const std::string &data, cpr::Session &session, AdditionalHeaders headers)
{
    auto multiform = params.attachments.has_value() && params.attachments.value().size() > 0;
    auto contentType = std::pair{"content-type", multiform ? "multipart/form-data" : "application/json"};
    headers.push_back(contentType);
    cpr::Header header{};
    std::copy(headers.begin(), headers.end(), 
          std::inserter(header, header.begin()));
    session.SetHeader(header);
    if (multiform)
    {
        cpr::Multipart mp {};
        mp.parts.emplace_back("payload_json", data, "application/json");
        for (auto &attachment : params.attachments.value())
        {
            auto &content = attachment.fileContent.value();
            cpr::Buffer b {content.begin(), content.end(), attachment.filename.value_or("")};
            auto name = fmt::format("files[{}]", (size_t) attachment.id);
            mp.parts.emplace_back(cpr::Part{name, b, attachment.contentType.value_or(std::string{})});
        }
        session.SetMultipart(std::move(mp));
    }
    else
        session.SetBody(data);
}