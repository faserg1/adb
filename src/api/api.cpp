#include "api.hpp"

#include <nlohmann/json.hpp>
#include <api/auth/auth.hpp>
#include <api/gateway/gateway.hpp>
#include <api/voice/gateway.hpp>
#include <api/gateway/gateway-retrive.hpp>
#include <api/channel/channel-api.hpp>
#include <api/guild/guild-api.hpp>
#include <api/interactions/interactions-api.hpp>
#include <api/user/user-api.hpp>

using namespace adb::api;

DiscordApi::DiscordApi() :
    baseUrl_("https://discord.com/api") // https://discord.com/developers/docs/reference#api-reference-base-url
{

}

std::unique_ptr<Auth> DiscordApi::CreateAuth()
{
    return std::unique_ptr<Auth>(new Auth(baseUrl_));
}

std::shared_ptr<Gateway> DiscordApi::GetGateway()
{
    if (gatewayInstance_)
        return gatewayInstance_;
    GatewayRetrive gr(baseUrl_);
    auto retriveData = gr.retriveBotGateway(GatewayRetriveQuery {
        .version = 9,
        .encoding = GatewayEncoding::JSON
    });
    auto intents = Intent::Guilds | Intent::GuildMessages | Intent::GuildVoiceStates;
    gatewayInstance_ = std::shared_ptr<Gateway>(new Gateway(retriveData.url, intents));
    return gatewayInstance_;
}

std::unique_ptr<VoiceGateway> DiscordApi::GetVoiceGateway(adb::types::SFID guildId)
{
    return std::unique_ptr<VoiceGateway>(new VoiceGateway(CreateUserApi(), GetGateway(), guildId));
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

std::unique_ptr<UserApi> DiscordApi::CreateUserApi()
{
    return std::unique_ptr<UserApi>(new UserApi(baseUrl_));
}
