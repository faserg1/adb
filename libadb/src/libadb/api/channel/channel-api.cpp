#include <libadb/api/channel/channel-api.hpp>
#include <nlohmann/json.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/fill-reason.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;
using namespace adb::types;

ChannelApi::ChannelApi(const std::string &baseUrl) :
    baseUrl_(baseUrl + "/channels")
{

}

std::vector<Message> ChannelApi::getMessages(adb::types::SFID channelId, std::optional<GetMessagesOpt> opt, std::optional<uint8_t> limit)
{
    auto url = fmt::format("{}/{}/messages",
        baseUrl_, channelId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto params = cpr::Parameters{};
    if (opt.has_value())
    {
        auto optVal = opt.value();
        std::string key;
        switch (optVal.type)
        {
            case GetMessagesOptType::After:
                key = "after";
                break;
            case GetMessagesOptType::Around:
                key = "around";
                break;
            case GetMessagesOptType::Before:
                key = "before";
                break;
        }
        if (!key.empty())
            params.Add(cpr::Parameter(key, optVal.messageId.to_string()));
    }
    if (limit.has_value())
    {
        params.Add(cpr::Parameter("limit", std::to_string(limit.value())));
    }
    session.SetParameters(params);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader()});
    auto response = session.Get();
    // todo: handle error
    nlohmann::json jresponse = nlohmann::json::parse(response.text);
    return jresponse.get<std::vector<Message>>();
}

bool ChannelApi::createReaction(adb::types::SFID channelId, adb::types::SFID messageId, std::string emoji)
{
    auto encodedEmoji = cpr::util::urlEncode(emoji);
    auto url = fmt::format("{}/{}/messages/{}/reactions/{}/@me",
        baseUrl_, channelId.to_string(), messageId.to_string(), encodedEmoji);
    auto response = cpr::Put(
        cpr::Url{url},
        cpr::Header{TokenBot::getBotAuthTokenHeader()},
        cpr::Payload{}
    );
    return response.status_code == 204;
}

std::optional<Message> ChannelApi::sendMessage(adb::types::SFID channelId, const SendMessageParams &params)
{
    auto url = fmt::format("{}/{}/messages",
        baseUrl_, channelId.to_string());
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
    auto response = session.Post();
    // todo: handle error
    nlohmann::json jresponse = nlohmann::json::parse(response.text);
    return jresponse.get<Message>();
}

std::optional<Message> ChannelApi::editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const SendMessageParams &params)
{
    auto url = fmt::format("{}/{}/messages/{}",
        baseUrl_, channelId.to_string(), messageId.to_string());
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

bool ChannelApi::bulkDeleteMessages(SFID channelId, std::vector<SFID> messageIds, std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/messages/bulk-delete",
        baseUrl_, channelId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    cpr::Header header{TokenBot::getBotAuthTokenHeader(), contentType};
    fillReason(header, reason);
    session.SetHeader(header);
    nlohmann::json j {
        {"messages", messageIds}
    };
    auto data = j.dump();
    session.SetBody(data);
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}