#include "api.hpp"

#include <nlohmann/json.hpp>
#include <api/auth/auth.hpp>
#include <api/gateway/gateway.hpp>
#include <api/gateway/gateway-retrive.hpp>
#include <api/channel/channel-api.hpp>
#include <api/guild/guild-api.hpp>
#include <api/interactions/interactions-api.hpp>

using namespace adb::api;

DiscordApi::DiscordApi() :
    baseUrl_("https://discord.com/api") // https://discord.com/developers/docs/reference#api-reference-base-url
{

}

std::unique_ptr<Auth> DiscordApi::CreateAuth()
{
    return std::unique_ptr<Auth>(new Auth(baseUrl_));
}

std::unique_ptr<Gateway> DiscordApi::CreateGateway()
{
    GatewayRetrive gr(baseUrl_);
    auto retriveData = gr.retriveBotGateway(GatewayRetriveQuery {
        .version = 9,
        .encoding = GatewayEncoding::JSON
    });
    return std::unique_ptr<Gateway>(new Gateway(retriveData.url));
}

std::unique_ptr<ChannelApi> DiscordApi::CreateChannelApi()
{
    return std::unique_ptr<ChannelApi>(new ChannelApi(baseUrl_));
}

std::unique_ptr<GuildApi> DiscordApi::CreateGuildApi()
{
    return std::unique_ptr<GuildApi>(new GuildApi(baseUrl_));
}

std::unique_ptr<InteractionsApi> DiscordApi::CreateInteractionsApi()
{
    return std::unique_ptr<InteractionsApi>(new InteractionsApi(baseUrl_));
}