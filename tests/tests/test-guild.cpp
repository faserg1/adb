#include "test-guild.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
using namespace adb::api;

auto testGuildId = adb::types::SFID{"918981635918159943"};

void checkGuildChannels(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto guildApi = api.CreateGuildApi();
    CreateGuildChannelParams params1
    {
        .name = "Bot Cat",
        .type = ChannelType::GUILD_CATEGORY,
    };
    auto category = guildApi->createChannel(testGuildId, params1, "For the sake of SATAN!");
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
    auto msgChannel = guildApi->createChannel(testGuildId, params2, "For the sake of SATAN!");
    auto voiceChannel = guildApi->createChannel(testGuildId, params3, "For the sake of SATAN!");
}

void checkRoleMemberAdd(adb::api::DiscordApi &api)
{
    auto guildApi = api.CreateGuildApi();
    guildApi->addMemberRole(testGuildId, adb::types::SFID{"294537448065859584"},adb::types::SFID{"964289645443706950"});
}

void checkGuildMembers(adb::api::DiscordApi &api)
{
    auto guildApi = api.CreateGuildApi();
    auto me = guildApi->getGuildMember(testGuildId, adb::types::SFID{"294537448065859584"});
    auto all = guildApi->listGuildMembers(testGuildId, 1000, {});
    auto search = guildApi->searchGuildMembers(testGuildId, "А", 1000);

    auto roles = guildApi->getRoles(testGuildId);
    int i = 0;
}