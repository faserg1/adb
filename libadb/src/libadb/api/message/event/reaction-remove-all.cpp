#include <libadb/api/message/event/reaction-remove-all.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageReactionRemoveAll& reactionAdd)
{
    j = nlohmann::json
    {
        {"channel_id", reactionAdd.channelId},
        {"message_id", reactionAdd.messageId},
    };
    map_to_json(j, "guild_id", reactionAdd.guildId);
}

void adb::api::from_json(const nlohmann::json& j, MessageReactionRemoveAll& reactionAdd)
{
    j.at("channel_id").get_to(reactionAdd.channelId);
    j.at("message_id").get_to(reactionAdd.messageId);
    map_from_json(j, "guild_id", reactionAdd.guildId);
}
