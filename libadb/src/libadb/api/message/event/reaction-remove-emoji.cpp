#include <libadb/api/message/event/reaction-remove-emoji.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageReactionRemoveEmoji& reactionAdd)
{
    j = nlohmann::json
    {
        {"channel_id", reactionAdd.channelId},
    };
    j["message_id"] = reactionAdd.messageId;
    map_to_json(j, "guild_id", reactionAdd.guildId);
    j["emoji"] = reactionAdd.emoji;
}

void adb::api::from_json(const nlohmann::json& j, MessageReactionRemoveEmoji& reactionAdd)
{
    j.at("channel_id").get_to(reactionAdd.channelId);
    map_from_json(j, "guild_id", reactionAdd.guildId);
    j.at("message_id").get_to(reactionAdd.messageId);
    j.at("emoji").get_to(reactionAdd.emoji);
}
