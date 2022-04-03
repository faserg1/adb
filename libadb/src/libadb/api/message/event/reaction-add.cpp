#include <libadb/api/message/event/reaction-add.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageReactionAdd& reactionAdd)
{
    j = nlohmann::json
    {
        {"user_id", reactionAdd.userId},
        {"channel_id", reactionAdd.channelId},
        {"message_id", reactionAdd.messageId},
    };
    map_to_json(j, "guild_id", reactionAdd.guildId);
    map_to_json(j, "member", reactionAdd.member);
    j["emoji"] = reactionAdd.emoji;
}

void adb::api::from_json(const nlohmann::json& j, MessageReactionAdd& reactionAdd)
{
    j.at("user_id").get_to(reactionAdd.userId);
    j.at("channel_id").get_to(reactionAdd.channelId);
    j.at("message_id").get_to(reactionAdd.messageId);
    map_from_json(j, "guild_id", reactionAdd.guildId);
    map_from_json(j, "member", reactionAdd.member);
    j.at("emoji").get_to(reactionAdd.emoji);
}
