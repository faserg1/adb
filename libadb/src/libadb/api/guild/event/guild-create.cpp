#include <libadb/api/guild/event/guild-create.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
using namespace adb::api;
using namespace adb::types;

// TODO: 

void adb::api::to_json(nlohmann::json& j, const GuildCreate& guild)
{
    to_json(j, *static_cast<const Guild*>(&guild));
    map_to_json(j, "joined_at", guild.joinedAt);
    map_to_json(j, "large", guild.large);
    map_to_json(j, "unavailable", guild.unavailable);
    map_to_json(j, "voice_states", guild.voiceStates);
    map_to_json(j, "members", guild.members);
    map_to_json(j, "channels", guild.channels);
    map_to_json(j, "threads", guild.threads);
}

void adb::api::from_json(const nlohmann::json& j, GuildCreate& guild)
{
    from_json(j, *static_cast<Guild*>(&guild));
    map_from_json(j, "joined_at", guild.joinedAt);
    map_from_json(j, "large", guild.large);
    map_from_json(j, "unavailable", guild.unavailable);
    map_from_json(j, "voice_states", guild.voiceStates);
    map_from_json(j, "members", guild.members);
    map_from_json(j, "channels", guild.channels);
    map_from_json(j, "threads", guild.threads);
}