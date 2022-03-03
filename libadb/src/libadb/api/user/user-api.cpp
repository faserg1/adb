#include <libadb/api/user/user-api.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
using namespace adb::api;

UserApi::UserApi(const std::string &baseUrl) :
    baseUrl_(baseUrl + "/users")
{

}

User UserApi::getCurrentUser()
{
    auto requestUrl = fmt::format("{}/@me", baseUrl_);
    auto response = cpr::Get(cpr::Url{requestUrl}, cpr::Header{TokenBot::getBotAuthTokenHeader()});
    auto json = nlohmann::json::parse(response.text);
    User user;
    json.get_to(user);
    return user;
}