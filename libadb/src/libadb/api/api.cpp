#include <libadb/api/api.hpp>

#include <libadb/api/context/context.hpp>
#include <nlohmann/json.hpp>
#include <libadb/api/auth/auth.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/media/media-gateway.hpp>
#include <libadb/api/gateway/gateway-retrive.hpp>
#include <libadb/api/channel/channel-api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/user/user-api.hpp>
#include <libadb/api/sticker/sticker-api.hpp>

#include <fmt/core.h>

using namespace adb::api;

namespace
{
    /// @details https://discord.com/developers/docs/reference#api-reference-base-url
    const std::string discordApiBaseUrl = "https://discord.com/api";
}

DiscordApi::DiscordApi(uint8_t version) :
    baseUrl_(fmt::format("{}/v{}", discordApiBaseUrl, version)),
    context_(std::make_shared<Context>(baseUrl_))
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

std::unique_ptr<MediaGateway> DiscordApi::GetMediaGateway(adb::types::SFID guildId)
{
    return std::unique_ptr<MediaGateway>(new MediaGateway(CreateUserApi(), GetGateway(), guildId));
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

std::unique_ptr<StickerApi> DiscordApi::CreateStickerApi()
{
    return std::unique_ptr<StickerApi>(new StickerApi(context_));
}