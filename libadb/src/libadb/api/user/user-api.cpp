#include <libadb/api/user/user-api.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <iostream>
using namespace adb::api;

UserApi::UserApi(const std::string &baseUrl) :
    baseUrl_(baseUrl + "/users")
{

}

User UserApi::getCurrentUser()
{
    auto requestUrl = fmt::format("{}/@me", baseUrl_);
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader()});
    auto response = session.Get();
    User user;
    if (response.status_code >= 200 && response.status_code < 300)
    {
        auto json = nlohmann::json::parse(response.text);
        json.get_to(user);
    }
    return user;
}

User UserApi::getUser(const adb::types::SFID id)
{
    auto requestUrl = fmt::format("{}/{}", baseUrl_, id.to_string());
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader()});
    auto response = session.Get();
    User user;
    if (response.status_code >= 200 && response.status_code < 300)
    {
        auto json = nlohmann::json::parse(response.text);
        json.get_to(user);
    }
    return user;
}

std::optional<Channel> UserApi::createDM(const adb::types::SFID recipientId)
{
    auto requestUrl = fmt::format("{}/@me/channels", baseUrl_);
    auto session = cpr::Session();
    session.SetUrl(cpr::Url{requestUrl});
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    nlohmann::json j
    {
        {"recipient_id", recipientId}
    };
    auto data = j.dump();
    session.SetBody(data);
    auto response = session.Post();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        auto json = nlohmann::json::parse(response.text);
        return json.get<Channel>();
    }
    return {};
}