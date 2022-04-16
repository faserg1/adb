#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/fill-reason.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/read-response.hpp>
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
    return readRequestResponse<std::vector<Channel>>(response);
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
    return readRequestResponseOpt<Channel>(response);
}

std::optional<GuildMember> GuildApi::getGuildMember(const adb::types::SFID &guildId, const adb::types::SFID &userId)
{
    auto url = fmt::format("{}/{}/members/{}",
        baseUrl_, guildId.to_string(), userId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    session.SetHeader(header);
    auto response = session.Get();
    return readRequestResponseOpt<GuildMember>(response);
}

std::vector<GuildMember> GuildApi::listGuildMembers(const adb::types::SFID &guildId,
    std::optional<uint64_t> limit, std::optional<adb::types::SFID> after)
{
    auto url = fmt::format("{}/{}/members",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    cpr::Parameters params;
    if (limit.has_value())
        params.Add(cpr::Parameter{"limit", std::to_string(limit.value())});
    if (after.has_value())
        params.Add(cpr::Parameter{"after", after.value().to_string()});
    session.SetParameters(params);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    session.SetHeader(header);
    auto response = session.Get();
    return readRequestResponse<std::vector<GuildMember>>(response);
}

std::vector<GuildMember> GuildApi::searchGuildMembers(const adb::types::SFID &guildId,
    std::string query, std::optional<uint64_t> limit)
{
    auto url = fmt::format("{}/{}/members/search",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    cpr::Parameters params;
    if (limit.has_value())
        params.Add(cpr::Parameter{"limit", std::to_string(limit.value())});
    params.Add(cpr::Parameter{"query", query});
    session.SetParameters(params);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    session.SetHeader(header);
    auto response = session.Get();
    return readRequestResponse<std::vector<GuildMember>>(response);
}

std::vector<Role> GuildApi::getRoles(const adb::types::SFID &guildId)
{
    auto url = fmt::format("{}/{}/roles",
        baseUrl_, guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    session.SetHeader(header);
    auto response = session.Get();
    return readRequestResponse<std::vector<Role>>(response);
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
    return readRequestResponseOpt<Role>(response);
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
    return readCommandResponse(response);
}

bool GuildApi::addMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
    std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/members/{}/roles/{}",
        baseUrl_, guildId.to_string(), userId.to_string(), roleId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType};
    fillReason(header, reason);
    session.SetHeader(header);
    // Empty body
    session.SetBody("{}");
    auto response = session.Put();
    return readCommandResponse(response);
}

bool GuildApi::removeMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
    std::optional<std::string> reason)
{
    auto url = fmt::format("{}/{}/members/{}/roles/{}",
        baseUrl_, guildId.to_string(), userId.to_string(), roleId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto header = cpr::Header{TokenBot::getBotAuthTokenHeader()};
    fillReason(header, reason);
    session.SetHeader(header);
    auto response = session.Delete();
    return readCommandResponse(response);
}