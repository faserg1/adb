#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/context/context.hpp>
#include <libadb/api/interactions/data/interaction-type.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/utils/message-session.hpp>
#include <libadb/api/utils/read-response.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
#include <algorithm>
using namespace adb::api;

InteractionsApi::InteractionsApi(std::shared_ptr<Context> context) :
    context_(context), baseUrl_(context->getBaseUrl()  + "/interactions"),
    webhooksUrl_(context_->getBaseUrl()  + "/webhooks"), appUrl_(context->getBaseUrl()  + "/applications")
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
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return readCommandResponse(response);
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
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Post();
    return readCommandResponse(response);
}

bool InteractionsApi::messageLater(const adb::types::SFID &interactionId, const std::string &token, std::optional<CreateMessageParams> params)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE}
    };
    if (params.has_value())
        json["data"] = params.value();
    auto data = json.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    if (params.has_value())
        fillSessionWithMessage(params.value(), data, session, {TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Post();
    return readCommandResponse(response);
}

bool InteractionsApi::autocomplete(const adb::types::SFID &interactionId, const std::string &token, std::vector<ApplicationCommandOptionChoice> choices)
{
    auto url = fmt::format("{}/{}/{}/callback",
        baseUrl_, interactionId.to_string(), token);
    auto data = nlohmann::json
    {
        {"choices", choices}
    };
    auto json = nlohmann::json
    {
        {"type", InteractionCallbackType::APPLICATION_COMMAND_AUTOCOMPLETE_RESULT},
        {"data", data}
    };
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return readCommandResponse(response);
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
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(json.dump());
    auto response = session.Post();
    return readCommandResponse(response);
}

std::optional<Message> InteractionsApi::editReply(const adb::types::SFID &appId, const std::string &token, const EditMessageParams &params)
{
    auto url = fmt::format("{}/{}/{}/messages/@original",
        webhooksUrl_, appId.to_string(), token);
    nlohmann::json j = params;
    auto data = j.dump();
    auto session = cpr::Session();
    session.SetUrl(url);
    fillSessionWithMessage(params, data, session, {TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Patch();
    return readRequestResponseOpt<Message>(response);
}

std::vector<ApplicationCommand> InteractionsApi::getGuildCommands(const adb::types::SFID &appId, const adb::types::SFID &guildId, bool withLocalization)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands", appUrl_, appId.to_string(), guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    session.SetParameters(cpr::Parameters {
        cpr::Parameter {"with_localizations", withLocalization ? "true" : "false"}
    });
    auto response = session.Get();
    return readRequestResponse<std::vector<ApplicationCommand>>(response);
}

std::optional<ApplicationCommand> InteractionsApi::createGuildCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const CreateApplicationCommandParams& params)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands", appUrl_, appId.to_string(), guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    nlohmann::json j = params;
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(j.dump());
    auto response = session.Post();
    return readRequestResponseOpt<ApplicationCommand>(response);
}

std::optional<ApplicationCommand> InteractionsApi::getGuildCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID &commandId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Get();
    return readRequestResponseOpt<ApplicationCommand>(response);
}

bool InteractionsApi::deleteGuldCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Delete();
    return readCommandResponse(response);
}

std::optional<std::vector<GuildApplicationCommandPermissions>> InteractionsApi::getGuildCommandPermissions(const adb::types::SFID &appId, const adb::types::SFID &guildId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/permissions", appUrl_, appId.to_string(), guildId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    auto response = session.Get();
    return readRequestResponse<std::vector<GuildApplicationCommandPermissions>>(response);
}

std::optional<GuildApplicationCommandPermissions> InteractionsApi::getCommandPermissions(
    const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId)
{
    auto url = fmt::format("{}/{}/guilds/{}/commands/{}/permissions", appUrl_, appId.to_string(), guildId.to_string(), commandId.to_string());
    auto session = cpr::Session();
    session.SetUrl(url);
    auto contentType = std::pair{"content-type", "application/json"};
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    auto response = session.Get();
    return readRequestResponseOpt<GuildApplicationCommandPermissions>(response);
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
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(j.dump());
    auto response = session.Put();
    return readRequestResponseOpt<GuildApplicationCommandPermissions>(response);
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
    // TODO: Client bearer token
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_), contentType});
    session.SetBody(j.dump());
    auto response = session.Put();
    return readRequestResponse<std::vector<GuildApplicationCommandPermissions>>(response);
}