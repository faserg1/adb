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