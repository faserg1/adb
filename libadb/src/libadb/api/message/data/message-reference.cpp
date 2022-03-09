#include <libadb/api/message/data/message-reference.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageReference& mention)
{
    j = nlohmann::json { };
    map_to_json(j, "message_id", mention.messageId);
    map_to_json(j, "channel_id", mention.channelId);
    map_to_json(j, "guild_id", mention.guildId);
    map_to_json(j, "fail_if_not_exists", mention.failIfNotExists);
}

void adb::api::from_json(const nlohmann::json& j, MessageReference& mention)
{
    map_from_json(j, "message_id", mention.messageId);
    map_from_json(j, "channel_id", mention.channelId);
    map_from_json(j, "guild_id", mention.guildId);
    map_from_json(j, "fail_if_not_exists", mention.failIfNotExists);
}