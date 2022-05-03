#include <libadb/api/auth/auth.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <libadb/api/context/context.hpp>
#include <libadb/cfg/secrets.hpp>
#include <libadb/api/utils/read-response.hpp>
#include <fmt/core.h>
#include <cpr/cpr.h>
using namespace adb::api;
using namespace std::string_literals;

Auth::Auth(std::shared_ptr<Context> context) :
    context_(context),
    baseUrl_(context->getBaseUrl() + "/oauth2"s),
    // https://discord.com/developers/docs/topics/oauth2#shared-resources-oauth2-urls
    authUrl_(baseUrl_ + "/authorize"s),
    tokenUrl_(baseUrl_ + "/token"s),
    revokeUrl_(baseUrl_ + "/token/revoke"s)
{
    
}

std::optional<Application> Auth::getCurrentApplicationInfo()
{
    auto url = fmt::format("{}/applications/@me",
        baseUrl_);
    auto session = cpr::Session();
    session.SetUrl(url);
    session.SetHeader(cpr::Header{TokenBot::getBotAuthTokenHeader(context_)});
    auto response = session.Get();
    return readRequestResponseOpt<Application>(response);
}

std::string Auth::getBotAuthUrl(Permissions permissions, std::optional<adb::types::SFID> guildId, bool disableGuildSelect)
{
    std::string guildIdQuery;
    if (guildId)
        guildIdQuery = fmt::format("guild_id={}&", (uint64_t) (guildId.value()));
    return fmt::format("{}?client_id={}&scope={}&permissions={}&{}{}",
        authUrl_,
        (uint64_t) context_->getSecrets().clientId,
        "bot", // scope
        (uint64_t) permissions,
        guildIdQuery,
        disableGuildSelect ? "true" : "false"
    );
}