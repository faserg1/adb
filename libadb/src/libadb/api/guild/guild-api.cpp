#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/fill-reason.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;

GuildApi::GuildApi(const std::string &baseUrl) : baseUrl_(baseUrl  + "/guilds")
{

}

std::vector<Channel> GuildApi::getChannels(const adb::types::SFID &guildId) const
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

std::optional<Channel> GuildApi::createChannel(const adb::types::SFID &guildId,
    const CreateGuildChannelParams &params, std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/channels",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType};
    fillReason(header, reason);
    session.SetHeader(header);
    nlohmann::json j = params;
    auto data = j.dump();
    session.SetBody(data);
    auto response = session.Post();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<Channel>();
    }
    return {};
}

LIBADB_API std::vector<Role> GuildApi::getRoles(const adb::types::SFID &guildId)
{
    auto url = fmt::format("{}/{}/roles",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    session.SetHeader(header);
    auto response = session.Get();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<std::vector<Role>>();
    }
    return {};
}

std::optional<Role> GuildApi::createRole(const adb::types::SFID &guildId,
    const CreateGuildRoleParams &params, std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/roles",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType};
    fillReason(header, reason);
    session.SetHeader(header);
    nlohmann::json j = params;
    auto data = j.dump();
    session.SetBody(data);
    auto response = session.Post();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<Role>();
    }
    return {};
}

bool GuildApi::deleteRole(const adb::types::SFID &guildId,
    const adb::types::SFID &roleId, std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/roles/{}",
        baseUrl_, guildId.to_string(), roleId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    fillReason(header, reason);
    session.SetHeader(header);
    auto response = session.Delete();
    if (response.status_code >= 200 && response.status_code < 300)
        return true;
    return false;
}

bool GuildApi::addMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
    std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/members/{}/role/{}",
        baseUrl_, guildId.to_string(), userId.to_string(), roleId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    fillReason(header, reason);
    session.SetHeader(header);
    auto response = session.Put();
    if (response.status_code >= 200 && response.status_code < 300)
        return true;
    return false;
}

bool GuildApi::removeMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
    std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/members/{}/role/{}",
        baseUrl_, guildId.to_string(), userId.to_string(), roleId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    fillReason(header, reason);
    session.SetHeader(header);
    auto response = session.Delete();
    if (response.status_code >= 200 && response.status_code < 300)
        return true;
    return false;
}