#include <libadb/api/user/user-api.hpp>
#include <libadb/api/context/context.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <libadb/api/utils/read-response.hpp>
#include <fmt/core.h>
#include <iostream>
using namespace adb::api;

UserApi::UserApi(std::shared_ptr<Context> context) :
    context_(context), baseUrl_(context->getBaseUrl() + "/users")
{

}

std::optional<User> UserApi::getCurrentUser()
{
    auto requestUrl = fmt::format("{}/@me", baseUrl_);
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Get();
    return readRequestResponseOpt<User>(response);
}

std::optional<User> UserApi::getUser(const adb::types::SFID id)
{
    auto requestUrl = fmt::format("{}/{}", baseUrl_, id.to_string());
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Get();
    return readRequestResponseOpt<User>(response);
}

std::optional<Channel> UserApi::createDM(const adb::types::SFID recipientId)
{
    auto requestUrl = fmt::format("{}/@me/channels", baseUrl_);
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    nlohmann::json j
    {
        {"recipient_id", recipientId}
    };
    auto data = j.dump();
    session.SetBody(data);
    auto response = session.Post();
    return readRequestResponseOpt<Channel>(response);
}