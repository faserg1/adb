#include "test1.hpp"

#include <iostream>
#include <vector>
#include <libadb/api/api.hpp>
#include <libadb/api/auth/auth.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/interactions/data/select-option.hpp>
#include <libadb/api/interactions/data/select-menu-component.hpp>
#include <libadb/api/interactions/data/action-row-component.hpp>
#include <libadb/api/interactions/data/button-component.hpp>
#include <libadb/api/interactions/data/text-input-component.hpp>
#include <libadb/api/channel/channel-api.hpp>
#include <libadb/api/error/endpoint-error.hpp>
#include <libadb/api/guild/guild-api.hpp>
#include <nlohmann/json.hpp>
#include <libadb/api/utils/msg-format.hpp>
#include <fmt/format.h>

using namespace adb::api;
using namespace adb::types;

void checkSmth(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway)
{
    auto channelApi = api.CreateChannelApi();
	
	auto sub = gateway->events()->subscribe<adb::api::Message>(adb::api::Event::MESSAGE_CREATE, [&channelApi](auto ev, auto &msg)
	{
		if (msg.author.bot && msg.author.bot.value())
			return;
		if (msg.content != "!test")
			return;
		auto msgMention = MessageReference {
			.messageId = msg.id
		};
		auto embed1 = Embed {
			.title = "История о том, как бот нахуй посылает",
			.description = "Хуй"
		};
		auto now = std::chrono::system_clock::now();
		auto embDesc = fmt::format("Привет {}, также известный как {}!\nЯ {} на канале {} дал тебе пизды.", 
			MsgFormat::mentionUser(msg.author.id),
			MsgFormat::mentionNickname(msg.author.id),
			MsgFormat::timestamp(now, MsgFormat::TimeStyle::RelativeTime),
			MsgFormat::mentionChannel(msg.channelId));
		auto embed2 = Embed {
			.title = "История",
			.description = embDesc
		};
		auto embeds = std::vector{embed1, embed2};
		auto opts = std::vector {
			SelectOption {
				.label = "X",
				.value = "X"
			},
			SelectOption {
				.label = "Y",
				.value = "Y"
			},
		};
		std::vector<MessageComponent> components;
		components.push_back(createSelectMenu(SelectMenuComponent {
			.customId = "chooser-looser",
			.options = opts,
			.placeholder = "Choose a coordinate",
		}));
		auto actionRows = std::vector<MessageComponent>{
			createActionRow(ActionRowComponent{
				.components = components
			})
		};
		auto attachments = std::vector
		{
			SendAttachment
			{
				.id = 0,
				.filename = "text.txt",
				.fileContent = std::vector<std::byte>{std::byte{0x55}, std::byte{0x55}, std::byte{0x55}, std::byte{0x0}}
			}
		};
		auto createdMsg = channelApi->createMessage(msg.channelId, {
			.content = "Fuck you!",
			.embeds = embeds,
			.messageReference = msgMention,
			.components = actionRows,
			.attachments = attachments
		});
		if (createdMsg)
			channelApi->createReaction(createdMsg.value().channelId, createdMsg.value().id, "👌");
	});
	auto sub2 = gateway->events()->subscribe(adb::api::Event::INTERACTION_CREATE, [&channelApi](auto ev, auto &msg)
	{
		int i = 0;
	});
}

void checkForErrors(adb::api::DiscordApi &api)
{
	auto channelApi = api.CreateChannelApi();
	try
	{
	}
	catch (adb::api::EndpointError &error)
	{
		int i = 0;
	}
}

void checkCurrentApp(adb::api::DiscordApi &api)
{
	auto auth = api.CreateAuth();
	auto app = auth->getCurrentApplicationInfo();
}