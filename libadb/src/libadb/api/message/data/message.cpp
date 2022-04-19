#include <libadb/api/message/data/message.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Message& msg)
{
    // TODO: Save for cache
}

void adb::api::from_json(const nlohmann::json& j, Message& msg)
{
    j.at("id").get_to(msg.id);
    j.at("channel_id").get_to(msg.channelId);
    map_from_json(j, "guild_id", msg.guildId);
    j.at("author").get_to(msg.author);
    map_from_json(j, "member", msg.guildMember);
    if (msg.guildId.has_value() && msg.guildMember.has_value())
    {
        std::optional<adb::types::SFID> userId = msg.author.id;
        gm_parse_avatar(msg.guildId.value(), userId, j["member"], msg.guildMember.value());
    }
    j.at("content").get_to(msg.content);
    j.at("timestamp").get_to(msg.timestamp);
    map_from_json(j, "edited_timestamp", msg.editedTimestamp);
    j.at("tts").get_to(msg.tts);
    j.at("mention_everyone").get_to(msg.mentionEveryone);
    j.at("mentions").get_to(msg.mentions);
    j.at("mention_roles").get_to(msg.mentionRoles);
    map_from_json(j, "mention_channels", msg.mentionChannels);
    j.at("attachments").get_to(msg.attachments);
    j.at("embeds").get_to(msg.embeds);
    map_from_json(j, "reactions", msg.reactions);
    map_from_json(j, "nonce", msg.nonce);
    j.at("pinned").get_to(msg.pinned);
    map_from_json(j, "webhook_id", msg.webhookId);
    j.at("type").get_to(msg.type);
    map_from_json(j, "activity", msg.activity);
    map_from_json(j, "application", msg.application);
    map_from_json(j, "application_id", msg.applicationId);
    map_from_json(j, "message_reference", msg.messageReference);
    map_from_json(j, "flags", msg.flags);
    map_from_json(j, "referenced_message", msg.referencedMessage);
    map_from_json(j, "interaction", msg.interaction);
    map_from_json(j, "thread", msg.thread);
    map_from_json(j, "components", msg.components);
    map_from_json(j, "sticker_items", msg.stickerItems);
}
