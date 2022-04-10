#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/interactions/data/interaction-type.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/message-session.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
#include <algorithm>
using namespace adb::api;

InteractionsApi::InteractionsApi(const std::string &baseUrl) :
    baseUrl_(baseUrl  + "/interactions"), webhooksUrl_(baseUrl  + "/webhooks"), appUrl_(baseUrl  + "/applications")
{

}

bool InteractionsApi::ack(const adb::types::SFID &interactionId, const std::string &token)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
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
    return response.status_code >= 200 && response.status_code < 300;
}

bool InteractionsApi::message(const adb::types::SFID &interactionId, const std::string &token, const CreateMessageParams &params)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::CHANNEL_MESSAGE_WITH_SOURCE},
        {"data", params}
    };
    auto data = json.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader()});
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

bool InteractionsApi::messageLater(const adb::types::SFID &interactionId, const std::string &token)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE}
    };
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

bool InteractionsApi::modal(const adb::types::SFID &interactionId, const std::string &token, const adb::api::Modal &modal)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::MODAL},
        {"data", modal}
    };
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return response.status_code >= 200 && response.status_code < 300;
}

std::optional<Message> InteractionsApi::editReply(const adb::types::SFID &appId, const std::string &token, const EditMessageParams &params)
{
    auto url = fmt::format("{}/{}/{}/messages/@original",
        webhooksUrl_, appId.to_string(), token);
    nlohmann::json j = params;
    auto data = j.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader()});
    auto response = session.Patch();
    // todo: handle error
    nlohmann::json jresponse = nlohmann::json::parse(response.text);
    return jresponse.get<Message>();
}

std::optional<ApplicationCommand> InteractionsApi::createGuildCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const CreateApplicationCommandParams& params)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands", appUrl_, appId.to_string(), guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    nlohmann::json j = params;
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(j.dump());
    auto response = session.Post();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<ApplicationCommand>();
    }
    return {};
}

bool InteractionsApi::deleteGuldCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader()});
    auto response = session.Delete();
    return response.status_code >= 200 && response.status_code < 300;
}

std::optional<std::vector<GuildApplicationCommandPermissions>> InteractionsApi::getGuildCommandPermissions(const adb::types::SFID &appId, const adb::types::SFID &guildId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/permissions", appUrl_, appId.to_string(), guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    auto response = session.Get();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<std::vector<GuildApplicationCommandPermissions>>();
    }
    return {};
}

std::optional<GuildApplicationCommandPermissions> InteractionsApi::getCommandPermissions(
    const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}/permissions", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    auto response = session.Get();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<GuildApplicationCommandPermissions>();
    }
    return {};
}

std::optional<GuildApplicationCommandPermissions> InteractionsApi::editCommandPermissions(
    const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId,
    const std::vector<ApplicationCommandPermission> &permissions)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}/permissions", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    auto j = nlohmann::json
    {
        {"permissions", permissions}
    };
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(j.dump());
    auto response = session.Put();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<GuildApplicationCommandPermissions>();
    }
    return {};
}

std::optional<std::vector<GuildApplicationCommandPermissions>> InteractionsApi::batchEditCommandPermissions(
    const adb::types::SFID &appId, const adb::types::SFID &guildId,
    const std::vector<GuildApplicationCommandPermissions> &permissions)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/permissions", appUrl_, appId.to_string(), guildId.to_string());
    nlohmann::json j = permissions;
    for (auto &permission : j)
    {
        permission.erase("application_id");
        permission.erase("guild_id");
    }
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(), contentType});
    session.SetBody(j.dump());
    auto response = session.Put();
    if (response.status_code >= 200 && response.status_code < 300)
    {
        nlohmann::json jresponse = nlohmann::json::parse(response.text);
        return jresponse.get<std::vector<GuildApplicationCommandPermissions>>();
    }
    return {};
}