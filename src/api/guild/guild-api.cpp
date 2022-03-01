#include "guild-api.hpp"
#include <api/auth/token-bot.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;

GuildApi::GuildApi(const std::string &baseUrl) : baseUrl_(baseUrl  + "/guilds")
{

}

std::vector<Channel> GuildApi::getChannels(adb::types::SFID guildId) const
{
    auto url = fmt::format("{}/{}/channels",
        baseUrl_, guildId.to_string());
    auto response = cpr::Get(
        cpr::Url{url},
        cpr::Header{TokenBot::getBotAuthTokenHeader()},
        cpr::Payload{}
    );
    nlohmann::json jresponse = nlohmann::json::parse(response.text);
    std::vector<Channel> channels;
    jresponse.get_to(channels);
    return channels;
}