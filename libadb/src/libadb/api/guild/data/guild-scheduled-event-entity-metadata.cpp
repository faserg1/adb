#include <libadb/api/guild/data/guild-scheduled-event-entity-metadata.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const GuildScheduledEventEntityMetadata& metadata)
{
    j = nlohmann::json {};
    map_to_json(j, "location", metadata.location);
}

void adb::api::from_json(const nlohmann::json& j, GuildScheduledEventEntityMetadata& metadata)
{
    map_from_json(j, "location", metadata.location);
}