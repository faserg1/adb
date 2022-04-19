#include "test-voice.hpp"

#include <iostream>
#include <vector>
#include <ranges>
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/media/media-gateway.hpp>
#include <libadb/api/interactions/data/interaction.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/channel/channel-api.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <libadb/api/interactions/interactions-api.hpp>
#include <libadb/api/interactions/data/action-row-component.hpp>
#include <libadb/api/interactions/data/select-menu-component.hpp>
#include <nlohmann/json.hpp>
#include <libadb/api/utils/msg-format.hpp>
#include <fmt/format.h>

using namespace adb::api;
using namespace adb::types;

TestVoice::TestVoice(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway) :
    api_(api), gateway_(gateway), channelApi_(api_.CreateChannelApi())
{
    mediaGateway_ = api.GetMediaGateway(adb::types::SFID{"918981635918159943"});
    init();
}

TestVoice::~TestVoice() = default;

void TestVoice::init()
{
    subs_.emplace_back(gateway_->events()->subscribe<adb::api::Message>(adb::api::Event::MESSAGE_CREATE, [this](auto ev, auto &msg)
	{
        if (msg.author.bot && msg.author.bot.value())
			return;
        if (msg.content == "!ts-bridge")
            onMessageChoose(msg.channelId);
        if (msg.content == "!ts-bridge stop")
            onDisconnect();
    }));
    subs_.emplace_back(gateway_->events()->subscribe<adb::api::Interaction>(adb::api::Event::INTERACTION_CREATE, [this](auto ev, auto &msg)
	{
        auto act = api_.CreateInteractionsApi();
        

        if (msg.type != InteractionType::MESSAGE_COMPONENT)
            return;

        std::string token = msg.token;
        adb::types::SFID id = msg.id;
        adb::types::SFID appId = msg.applicationId;
        std::vector<std::string> values;

        auto data = adb::api::getInteractionData<InteractionDataComponent>(msg);

        if (data.has_value())
        {
            if (data.value()->customId != "ts-bridge-choose-channel")
                return;
            if (data.value()->values.has_value())
                values = data.value()->values.value();
            
        }


        act->messageLater(id, token);
        
        if (values.empty())
        {
            act->editReply(appId, token, EditMessageParams
            {
                .content = std::string {"Channel not choosed!"},
                .flags = 0 | MessageFlag::EPHEMERAL
            });
            return;
        }
        auto thread = std::thread([this, values, id, appId, token, act = std::move(act)]()
        {
            auto result = onMessageConnect(adb::types::SFID{values.front()}).get();
            if (result)
            {
                act->editReply(appId, token, EditMessageParams
                {
                    .content = std::string {"Connected"},
                    .flags = 0 | MessageFlag::EPHEMERAL
                });
                voiceDataThreadReceiver = std::jthread([this](std::stop_token stop)
                {
                    receiveWorker(stop);
                });
            }
            else
            {
                act->editReply(appId, token, EditMessageParams
                {
                    .content = std::string {"Connection failed!"},
                    .flags = 0 | MessageFlag::EPHEMERAL
                });
            }
        });
		thread.detach();
	}));
}

void TestVoice::onMessageChoose(adb::types::SFID channelId)
{
    if (onConnected_)
        return;
    auto guildApi = api_.CreateGuildApi();

    auto channels = guildApi->getChannels(adb::types::SFID{"918981635918159943"});
    auto onlyVoice = channels | std::views::filter([](Channel &channel) { return channel.type == ChannelType::GUILD_VOICE;} );

    std::vector<SelectOption> opts;

    std::transform(onlyVoice.begin(), onlyVoice.end(), std::back_inserter(opts), [](Channel &channel) {
        return SelectOption {
            .label = channel.name.has_value() ? channel.name.value() : channel.id.to_string(),
            .value = channel.id.to_string()  
        };
    });
    
    std::vector<MessageComponent> components;
    SelectMenuComponent selectMenu {
        .customId = "ts-bridge-choose-channel",
        .options = opts,
        .placeholder = "Choose a channel",
    };
    components.push_back(createSelectMenu(selectMenu));
    std::vector<MessageComponent> actionRows;
    ActionRowComponent actionRow {
        .components = components
    };
    actionRows.push_back(createActionRow(actionRow));
    auto channelApi = api_.CreateChannelApi();
    auto createdMsg = channelApi->createMessage(channelId, {
        .components = actionRows,
    });
}

void TestVoice::receiveWorker(std::stop_token stop)
{
    while (!stop.stop_requested())
    {
        auto packet = mediaGateway_->receivePacket().get();
        std::cout << fmt::format("Packet {:#x} {:#x}", packet.vpxcc, packet.mpt) << std::endl;
    }
}

std::future<bool> TestVoice::onMessageConnect(adb::types::SFID channelId)
{
    return mediaGateway_->connect(channelId, false, false);
}

void TestVoice::onDisconnect()
{
    std::thread thread([this]()
    {
        auto future = mediaGateway_->disconnect();
    });
    thread.detach();
    
}