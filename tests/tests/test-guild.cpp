#include "test-guild.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
using namespace adb::api;

void checkGuildChannels(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto guildApi = api.CreateGuildApi();
    CreateGuildChannelParams params1
    {
        .name = "Bot Cat",
        .type = ChannelType::GUILD_CATEGORY,
    };
    auto category = guildApi->createChannel({"918981635918159943"}, params1, "For the sake of SATAN!");
    CreateGuildChannelParams params2
    {
        .name = "Bot Msg",
        .type = ChannelType::GUILD_TEXT,
        .parentId = category.value().id
    };
    CreateGuildChannelParams params3
    {
        .name = "Bot Voice",
        .type = ChannelType::GUILD_VOICE,
        .parentId = category.value().id
    };
    auto msgChannel = guildApi->createChannel({"918981635918159943"}, params2, "For the sake of SATAN!");
    auto voiceChannel = guildApi->createChannel({"918981635918159943"}, params3, "For the sake of SATAN!");
}