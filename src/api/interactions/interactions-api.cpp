#include "interactions-api.hpp"
#include <api/interactions/data/interaction-type.hpp>
#include <api/auth/token-bot.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;

InteractionsApi::InteractionsApi(const std::string &baseUrl) : baseUrl_(baseUrl  + "/interactions")
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
    return response.status_code == 200;
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
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return response.status_code == 200;
}