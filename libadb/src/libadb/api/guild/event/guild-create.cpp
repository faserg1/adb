#include <libadb/api/guild/event/guild-create.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const GuildCreate& guild)
{
    to_json(j, *static_cast<const Guild*>(&guild));
}

void adb::api::from_json(const nlohmann::json& j, GuildCreate& guild)
{
    from_json(j, *static_cast<Guild*>(&guild));
}