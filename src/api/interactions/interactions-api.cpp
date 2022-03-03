#include "interactions-api.hpp"
#include <api/interactions/data/interaction-type.hpp>
#include <api/auth/token-bot.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;

InteractionsApi::InteractionsApi(const std::string &baseUrl) :
    baseUrl_(baseUrl  + "/interactions"), webhooksUrl_(baseUrl  + "/webhooks")
{

}

bool InteractionsApi::ack(const adb::types::SFID &id, const std::string &token)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, id.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::PONG}
    };
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

bool InteractionsApi::message(const adb::types::SFID &id, const std::string &token, const SendMessageParams &params)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, id.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::CHANNEL_MESSAGE_WITH_SOURCE},
        {"data", params}
    };
    auto data = json.dump();
    auto session = cpr::Session();
    auto multiform = params.attachments.has_value() && params.attachments.value().size() > 0;
    auto contentType = std::pair{"content-type", multiform ? "multipart/form-data" : "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
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
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

bool InteractionsApi::messageLater(const adb::types::SFID &id, const std::string &token)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, id.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE}
    };
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

std::optional<Message> InteractionsApi::editReply(const adb::types::SFID &appId, const std::string &token, const SendMessageParams &params)
{
    auto url = fmt::format("{}/{}/{}/messages/@original",
        webhooksUrl_, appId, token);
    nlohmann::json j = params;
    auto data = j.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    auto multiform = params.attachments.has_value() && params.attachments.value().size() > 0;
    auto contentType = std::pair{"content-type", multiform ? "multipart/form-data" : "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
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
    auto response = session.Patch();
    // todo: handle error
    nlohmann::json jresponse = nlohmann::json::parse(response.text);
    return jresponse.get<Message>();
}