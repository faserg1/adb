#include "app-commands.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/user/user-api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/interactions/data/interaction.hpp>
#include <libadb/api/interactions/data/text-input-component.hpp>
#include <libadb/api/interactions/data/button-component.hpp>
#include <libadb/api/interactions/data/action-row-component.hpp>
#include <libadb/cfg/secrets.hpp>
using namespace adb::api;

static std::unique_ptr<adb::types::Subscription> cmdSub;
const adb::types::SFID guildId{"918981635918159943"};

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
    auto cmd1 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), guildId, commandParams1);
    auto cmd2 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), guildId, commandParams2);
    auto cmd3 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), guildId, commandParams3);

    auto allPerms = ixApi->getGuildCommandPermissions(adb::cfg::Secrets::GetAppId(), guildId);
    auto perms1 = ixApi->getCommandPermissions(adb::cfg::Secrets::GetAppId(), guildId, cmd2.value().id);

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

    auto cmd4 = ixApi->createGuildCommand(adb::cfg::Secrets::GetAppId(), guildId, commandParams4);

    cmdSub = gateway->events()->subscribe<adb::api::Interaction>(adb::api::Event::INTERACTION_CREATE, [&api](auto ev, auto &msg)
	{
        auto ixApi = api.CreateInteractionsApi();
        auto userApi = api.CreateUserApi();
        auto guildApi = api.CreateGuildApi();
        if (msg.type != InteractionType::APPLICATION_COMMAND)
            return;
        auto data = std::static_pointer_cast<InteractionDataApplicationCommand>(msg.data.value());

        if (data->name != "duck1")
            return;
        auto sameUser = userApi->getUser(msg.guildMember.value().user.value().id);
        auto roleParams = CreateGuildRoleParams
        {
            .name = "wow",
        };
        auto role = guildApi->createRole(guildId, roleParams, "We did it!");
        guildApi->addMemberRole(guildId, sameUser.id, role.value().id, "We adding role!");
        guildApi->removeMemberRole(guildId, sameUser.id, role.value().id, "We removing role!");
        guildApi->deleteRole(guildId, role.value().id, "Fuck that role!");
        auto textInput = createTextInput(TextInputComponent {
            .customId = "lol",
            .style = TextInputStyle::Short,
            .label = "You know what"
        });
        auto actionRow = createActionRow(ActionRowComponent {
            .components = {textInput}
        });
        ixApi->modal(msg.id, msg.token, Modal {
            .customId = "test-modal",
            .title = "Get on",
            .components = {
                actionRow
            }
        });
    });
}