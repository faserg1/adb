#include <libadb/api/guild/data/guild-scheduled-event.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/resource/image-resolver.hpp>
using namespace adb::api;
using namespace adb::types;
using namespace adb::resource;

void adb::api::to_json(nlohmann::json& j, const GuildScheduledEvent& event)
{
    j = nlohmann::json
    {
        {"id", event.id},
        {"guild_id", event.guildId}
    };
    map_to_json(j, "channel_id", event.channelId);
    map_to_json(j, "creator_id", event.creatorId);
    j["name"] = event.name;
    map_to_json(j, "description", event.description);
    j["scheduled_start_time"] = event.scheduledStartTime;
    map_to_json(j, "scheduled_end_time", event.scheduledEndTime);
    j["privacy_level"] = event.privacyLevel;
    j["entity_type"] = event.entityType;
    map_to_json(j, "entity_id", event.entityId);
    j["creator"] = event.creator;
    map_to_json(j, "user_count", event.userCount);
    map_to_json(j, "image", event.image);
}

void adb::api::from_json(const nlohmann::json& j, GuildScheduledEvent& event)
{
    j.at("id").get_to(event.id);
    j.at("guild_id").get_to(event.guildId);
    map_from_json(j, "channel_id", event.channelId);
    map_from_json(j, "creator_id", event.creatorId);
    j.at("name").get_to(event.name);
    map_from_json(j, "description", event.description);
    j.at("scheduled_start_time").get_to(event.scheduledStartTime);
    map_from_json(j, "scheduled_end_time", event.scheduledEndTime);
    j.at("privacy_level").get_to(event.privacyLevel);
    j.at("entity_type").get_to(event.entityType);
    map_from_json(j, "entity_id", event.entityId);
    j.at("creator").get_to(event.creator);
    map_from_json(j, "user_count", event.userCount);
    if (j.contains("image"))
        event.image.emplace(ImageResolver::getGuildScheduledEventCover(event.id, j.at("image").get<std::string>()));
}