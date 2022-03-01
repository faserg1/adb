#include "test-voice.hpp"

#include <iostream>
#include <vector>
#include <ranges>
#include <api/api.hpp>
#include <api/gateway/gateway.hpp>
#include <api/voice/gateway.hpp>
#include <api/gateway/gateway-events.hpp>
#include <api/message/data/message.hpp>
#include <api/channel/channel-api.hpp>
#include <api/guild/guild-api.hpp>
#include <api/interactions/interactions-api.hpp>
#include <nlohmann/json.hpp>
#include <api/utils/msg-format.hpp>
#include <fmt/format.h>

using namespace adb::api;
using namespace adb::types;

TestVoice::TestVoice(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway) :
    api_(api), gateway_(gateway), channelApi_(api_.CreateChannelApi())
{
    voiceGateway_ = api.GetVoiceGateway(adb::types::SFID{"918981635918159943"});
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
    subs_.emplace_back(gateway_->events()->subscribe(adb::api::Event::INTERACTION_CREATE, [this](auto ev, auto &msg)
	{
        auto act = api_.CreateInteractionsApi();
        std::string token;
        adb::types::SFID id;
        std::vector<std::string> values;
        msg["id"].get_to(id);
        msg["token"].get_to(token);
        msg["data"]["values"].get_to(values);
        
        if (values.empty())
        {
            act->message(id, token, SendMessageParams
            {
                .content = std::string {"Channel not choosed!"},
            });
            return;
        }
		onMessageConnect(adb::types::SFID{values.front()});
        act->message(id, token, SendMessageParams
        {
            .content = std::string {"Connecting..."},
        });
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
    
    auto components = std::vector {
        MessageComponent {
            .type = MessageComponentType::SelectMenu,
            .customId = "ts-bridge-choose-channel",
            .options = opts,
            .placeholder = "Choose a channel",
        },
    };
    auto actionRows = std::vector{
        MessageComponent {
            .type = MessageComponentType::ActionRow,
            .components = components
        }
    };
    auto channelApi = api_.CreateChannelApi();
    auto createdMsg = channelApi->sendMessage(channelId, {
        .components = actionRows,
    });
}

void TestVoice::onMessageConnect(adb::types::SFID channelId)
{
    voiceGateway_->connect(channelId, false, false);
}

void TestVoice::onDisconnect()
{
    voiceGateway_->disconnect();
}