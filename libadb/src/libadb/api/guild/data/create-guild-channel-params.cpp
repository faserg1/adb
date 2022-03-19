#include <libadb/api/guild/data/create-guild-channel-params.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const CreateGuildChannelParams& params)
{
    j = nlohmann::json
    {
        {"name", params.name}
    };
    map_to_json(j, "type", params.type);
    map_to_json(j, "topic", params.topic);
    map_to_json(j, "bitrate", params.bitrate);
    map_to_json(j, "user_limit", params.userLimit);
    map_to_json(j, "rate_limit_per_user", params.rateLimitPerUser);
    map_to_json(j, "position", params.position);
    map_to_json(j, "permission_overwrites", params.permissionOverwrites);
    map_to_json(j, "parent_id", params.parentId);
    map_to_json(j, "nsfw", params.nsfw);
}

void adb::api::from_json(const nlohmann::json& j, CreateGuildChannelParams& params)
{
    j.at("name").get_to(params.name);
    map_from_json(j, "type", params.type);
    map_from_json(j, "topic", params.topic);
    map_from_json(j, "bitrate", params.bitrate);
    map_from_json(j, "user_limit", params.userLimit);
    map_from_json(j, "rate_limit_per_user", params.rateLimitPerUser);
    map_from_json(j, "position", params.position);
    map_from_json(j, "permission_overwrites", params.permissionOverwrites);
    map_from_json(j, "parent_id", params.parentId);
    map_from_json(j, "nsfw", params.nsfw);
}