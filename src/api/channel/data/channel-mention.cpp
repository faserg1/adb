#include "channel-mention.hpp"
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const ChannelMention& mention)
{
    j = nlohmann::json
    {
        {"id", mention.id},
        {"guild_id", mention.guildId},
        {"type", mention.type},
        {"name", mention.name},
    };
}

void adb::api::from_json(const nlohmann::json& j, ChannelMention& mention)
{
    j.at("id").get_to(mention.id);
    j.at("guild_id").get_to(mention.guildId);
    j.at("type").get_to(mention.type);
    j.at("name").get_to(mention.name);
}