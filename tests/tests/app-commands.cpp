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
        .defaultPermission = false,
        .type = ApplicationCommandType::USER
    };
    auto commandParams3 = CreateApplicationCommandParams {
        .name = "Duck 3",
        .type = ApplicationCommandType::MESSAGE
    };
    auto cmd1 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams1);
    auto cmd2 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams2);
    auto cmd3 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams3);

    auto allPerms = ixApi->getGuildCommandPermissions(adb::cfg::Secrets::GetAppId(), {"918981635918159943"});
    auto perms1 = ixApi->getCommandPermissions(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, cmd2.value().id);

    std::vector<ApplicationCommandOption> opts = {
        ApplicationCommandOption {
            .type = ApplicationCommandOptionType::MENTIONABLE,
            .name = "loser",
            .description = "Loser in entire life",
            .required = true,
        },
        ApplicationCommandOption {
            .type = ApplicationCommandOptionType::STRING,
            .name = "kli4ka",
            .description = "How to name there",
            .required = false,
        },
    };

    std::vector<ApplicationCommandOption> sub = {
        ApplicationCommandOption {
            .type = ApplicationCommandOptionType::SUB_COMMAND,
            .name = "tick",
            .description = "A tick",
            .options = opts,
        }
    };

    std::vector<ApplicationCommandOption> subGroup = {
        ApplicationCommandOption {
            .type = ApplicationCommandOptionType::SUB_COMMAND_GROUP,
            .name = "tack",
            .description = "A tack",
            .options = sub,
        }
    };

    auto commandParams4 = CreateApplicationCommandParams {
        .name = "duck4",
        .description = "Duck 4",
        .options = subGroup
    };

    auto cmd4 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), {"918981635918159943"}, commandParams4);
}