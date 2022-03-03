#include <libadb/api/channel/data/channel.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Channel& channel)
{
    j = nlohmann::json
    {
        {"id", channel.id},
    };
}

void adb::api::from_json(const nlohmann::json& j, Channel& channel)
{
    j.at("id").get_to(channel.id);
    j.at("type").get_to(channel.type);
    map_from_json(j, "guild_id", channel.guildId);
    map_from_json(j, "position", channel.position);
    map_from_json(j, "permission_overwrites", channel.permissionOverwrites);
    map_from_json(j, "name", channel.name);
    map_from_json(j, "topic", channel.topic);
    map_from_json(j, "nsfw", channel.nsfw);
    map_from_json(j, "last_message_id", channel.lastMessageId);
    map_from_json(j, "bitrate", channel.bitrate);
    map_from_json(j, "user_limit", channel.userLimit);
    map_from_json(j, "rate_limit_per_user", channel.rateLimitPerUser);
    map_from_json(j, "recipients", channel.recipients);
    map_from_json(j, "icon", channel.iconHash);
}