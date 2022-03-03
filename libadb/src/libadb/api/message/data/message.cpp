#include <libadb/api/message/data/message.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Message& msg)
{

}

void adb::api::from_json(const nlohmann::json& j, Message& msg)
{
    j.at("id").get_to(msg.id);
    j.at("channel_id").get_to(msg.channelId);
    if (j.contains("guild_id"))
        j.at("guild_id").get_to(msg.guildId);
    j.at("author").get_to(msg.author);
    if (j.contains("member"))
        j.at("member").get_to(msg.member);
    j.at("content").get_to(msg.content);
    j.at("timestamp").get_to(msg.timestamp);
    if (j.contains("edited_timestamp"))
        j.at("edited_timestamp").get_to(msg.editedTimestamp);
}