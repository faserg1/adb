#include <libadb/api/interactions/data/resolved-data.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-sfid-map.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ResolvedData& data)
{
    map_to_json(j, "users", data.users);
    map_to_json(j, "members", data.members);
    map_to_json(j, "roles", data.roles);
    map_to_json(j, "channels", data.channels);
    map_to_json(j, "messages", data.messages);
    map_to_json(j, "attachments", data.attachments);
}

void adb::api::from_json(const nlohmann::json& j, ResolvedData& data)
{
    map_from_json(j, "users", data.users);
    map_from_json(j, "members", data.members);
    map_from_json(j, "roles", data.roles);
    map_from_json(j, "channels", data.channels);
    map_from_json(j, "messages", data.messages);
    map_from_json(j, "attachments", data.attachments);
}