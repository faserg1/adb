#include <libadb/api/emoji/data/emoji.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Emoji& emoji)
{
    j["id"] = emoji.id; // nullable
    j["name"] = emoji.name; // nullable
    map_to_json(j, "roles", emoji.roleIds);
    map_to_json(j, "user", emoji.user);
    map_to_json(j, "require_colons", emoji.requireColons);
    map_to_json(j, "managed", emoji.managed);
    map_to_json(j, "animated", emoji.animated);
    map_to_json(j, "available", emoji.available);
}

void adb::api::from_json(const nlohmann::json& j, Emoji& emoji)
{
    j.at("id").get_to(emoji.id); // nullable
    j.at("name").get_to(emoji.name); // nullable
    map_from_json(j, "roles", emoji.roleIds);
    map_from_json(j, "user", emoji.user);
    map_from_json(j, "require_colons", emoji.requireColons);
    map_from_json(j, "managed", emoji.managed);
    map_from_json(j, "animated", emoji.animated);
    map_from_json(j, "available", emoji.available);
}