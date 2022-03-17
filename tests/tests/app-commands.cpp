#include "app-commands.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/cfg/secrets.hpp>
using namespace adb::api;

void checkAppCommands(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto ixApi = api.CreateInteractionsApi();
    auto commandParams1 = CreateApplicationCommandParams {
        .name = "duck1",
        .description = "Duck 1",
    };
    auto commandParams2 = CreateApplicationCommandParams {
        .name = "Duck 2",
        .type = ApplicationCommandType::USER
    };
    auto commandParams3 = CreateApplicationCommandParams {
        .name = "Duck 3",
        .type = ApplicationCommandType::MESSAGE
    };
    ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams1);
    ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams2);
    ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams3);
}