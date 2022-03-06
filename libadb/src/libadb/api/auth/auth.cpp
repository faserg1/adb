#include <libadb/api/auth/auth.hpp>
#include <libadb/cfg/secrets.hpp>
#include <fmt/core.h>
using namespace adb::api;
using namespace std::string_literals;

Auth::Auth(std::string_view baseUrl) :
    // https://discord.com/developers/docs/topics/oauth2#shared-resources-oauth2-urls
    authUrl_(std::string(baseUrl) + "/oauth2/authorize"s),
    tokenUrl_(std::string(baseUrl) + "/oauth2/token"s),
    revokeUrl_(std::string(baseUrl) + "/oauth2/token/revoke"s)
{
    
}

std::string Auth::getBotAuthUrl(Permissions permissions, std::optional<adb::types::SFID> guildId, bool disableGuildSelect)
{
    std::string guildIdQuery;
    if (guildId)
        guildIdQuery = fmt::format("guild_id={}&", (uint64_t) (guildId.value()));
    return fmt::format("{}?client_id={}&scope={}&permissions={}&{}{}",
        authUrl_,
        (uint64_t) adb::cfg::Secrets::GetClientId(),
        "bot", // scope
        (uint64_t) permissions,
        guildIdQuery,
        disableGuildSelect ? "true" : "false"
    );
}