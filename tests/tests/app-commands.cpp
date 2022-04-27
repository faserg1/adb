#include "app-commands.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/user/user-api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/channel/channel-api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/interactions/interactions.hpp>
#include <libadb/api/interactions/data/interaction.hpp>
#include <libadb/api/interactions/data/text-input-component.hpp>
#include <libadb/api/interactions/data/button-component.hpp>
#include <libadb/api/interactions/data/action-row-component.hpp>
#include "../cfg/secrets.hpp"
using namespace adb::api;

static std::vector<std::unique_ptr<adb::types::Subscription>> cmdSubs;
const adb::types::SFID guildId{"918981635918159943"};

void checkAppCommands(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto ixApi = api.CreateInteractionsApi();
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
            .autocomplete = true
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

    auto cmd4 = ixApi->createGuildCommand(Secrets::getSecrets().appId, guildId, commandParams4);

    cmdSubs.emplace_back(gateway->events()->subscribe<adb::api::Interaction>(adb::api::Event::INTERACTION_CREATE, [&api](auto ev, auto &msg)
	{
        auto ixApi = api.CreateInteractionsApi();
        auto userApi = api.CreateUserApi();
        auto channelApi = api.CreateChannelApi();
        auto guildApi = api.CreateGuildApi();
        if (msg.type != InteractionType::APPLICATION_COMMAND)
            return;
        auto data = std::static_pointer_cast<InteractionDataApplicationCommand>(msg.data.value());

        if (data->name != "duck1")
            return;
        CreateMessageParams params {
            .flags = 0 | MessageFlag::EPHEMERAL
        };
        ixApi->messageLater(msg.id, msg.token, params);
    }));
    cmdSubs.emplace_back(gateway->events()->subscribe<adb::api::Interaction>(adb::api::Event::INTERACTION_CREATE, [&api](auto ev, auto &msg)
	{
        auto ixApi = api.CreateInteractionsApi();
        auto userApi = api.CreateUserApi();
        auto channelApi = api.CreateChannelApi();
        auto guildApi = api.CreateGuildApi();
        if (msg.type != InteractionType::APPLICATION_COMMAND_AUTOCOMPLETE)
            return;
        auto data = std::static_pointer_cast<InteractionDataApplicationCommand>(msg.data.value());
        int i = 0;
    }));
}

void checkAppCommands2(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto ixApi = api.CreateInteractionsApi();
    auto commands = ixApi->getGuildCommands(Secrets::getSecrets().appId, guildId);
    for (auto command : commands)
    {
        ixApi->deleteGuldCommand(command.applicationId, command.guildId.value(), command.id);
    }
    int i = 0;
}

void checkAppCommands3(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto ixApi = api.CreateInteractionsApi();
    auto localization = std::unordered_map<adb::resource::Locale, std::string> {
        {adb::resource::Locale::Russian, std::string{"Утка 5"}}
    };
    auto commandParams5 = CreateApplicationCommandParams {
        .name = "Duck 5",
        .nameLocalizations = localization,
        .type = ApplicationCommandType::MESSAGE
    };

    auto cmd5 = ixApi->createGuildCommand(Secrets::getSecrets().appId, guildId, commandParams5);
    int i = 0;
}

void checkAppCommands4(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    Interactions ix(gateway->events());
    cmdSubs.emplace_back(ix.subscribeToCommand("cfg", {"role-add"}, [](auto &ix, auto &data, auto &lastOptions)
    {
        auto options = lastOptions.value_or(std::vector<InteractionDataCommandOption>{});
    }));
}

void checkAppCommands5(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto ixApi = api.CreateInteractionsApi();
    auto commandParams5 = CreateApplicationCommandParams {
        .name = "adb_zero",
        .description = "testing",
        .defaultPermission = false,
        .type = ApplicationCommandType::CHAT_INPUT,
    };
     auto commandParams6 = CreateApplicationCommandParams {
        .name = "adb_one",
        .description = "testing",
        .defaultPermission = false,
        .type = ApplicationCommandType::CHAT_INPUT,
    };
    auto appId = Secrets::getSecrets().appId;
    auto cmd5 = ixApi->createGuildCommand(appId, guildId, commandParams5);
    auto cmd6 = ixApi->createGuildCommand(appId, guildId, commandParams6);
    auto commands = {cmd5.value().id, cmd6.value().id};
    std::vector<GuildApplicationCommandPermissions> permissions;
    adb::types::SFID roleId{"964307674101608549"};
    std::transform(commands.begin(), commands.end(), std::back_inserter(permissions), [guildId = guildId, roleId, appId](auto &id) -> GuildApplicationCommandPermissions
    {
        std::vector<ApplicationCommandPermission> cmdPermissions
        {
            ApplicationCommandPermission
            {
                .id = roleId,
                .type = ApplicationCommandPermissionType::ROLE,
                .permission = true
            }
        };
        return GuildApplicationCommandPermissions
        {
            .id = id,
            .applicationId = appId,
            .guildId = guildId,
            .permissions = cmdPermissions
        };
    });
    ixApi->batchEditCommandPermissions(appId, guildId, permissions);
    int i = 0;
}