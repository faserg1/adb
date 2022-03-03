#include "test1.hpp"

#include <iostream>
#include <vector>
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/channel/channel-api.hpp>
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
		auto components = std::vector {
			MessageComponent {
				.type = MessageComponentType::SelectMenu,
				.customId = "chooser-looser",
				.options = opts,
				.placeholder = "Choose a coordinate",
			},
		};
		auto actionRows = std::vector{
			MessageComponent {
				.type = MessageComponentType::ActionRow,
				.components = components
			}
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
		auto createdMsg = channelApi->sendMessage(msg.channelId, {
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