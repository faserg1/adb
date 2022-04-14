#include <libadb/api/channel/channel-api.hpp>
#include <nlohmann/json.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/fill-reason.hpp>
#include <libadb/api/utils/message-session.hpp>
#include <libadb/api/utils/read-response.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
#include <algorithm>
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
    return readRequestResponse<std::vector<Message>>(response);
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
    return readCommandResponse(response);
}

std::optional<Message> ChannelApi::createMessage(adb::types::SFID channelId, const CreateMessageParams &params)
{
    auto url = fmt::format("{}/{}/messages",
        baseUrl_, channelId.to_string());
    nlohmann::json j = params;
    auto data = j.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader()});
    auto response = session.Post();
    return readRequestResponseOpt<Message>(response);
}

std::optional<Message> ChannelApi::editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const EditMessageParams &params)
{
    auto url = fmt::format("{}/{}/messages/{}",
        baseUrl_, channelId.to_string(), messageId.to_string());
    nlohmann::json j = params;
    auto data = j.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader()});
    auto response = session.Patch();
    return readRequestResponseOpt<Message>(response);
}

bool ChannelApi::deleteMessage(const adb::types::SFID &channelId, const adb::types::SFID &messageId, std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/messages/{}",
        baseUrl_, channelId.to_string(), messageId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    cpr::Header header{TokenBot::getBotAuthTokenHeader()};
    fillReason(header, reason);
    session.SetHeader(header);
    auto response = session.Delete();
    return readCommandResponse(response);
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
    return readCommandResponse(response);
}