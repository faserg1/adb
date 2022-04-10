#pragma once

#include <libadb/types/snowflake.hpp>
#include <optional>
#include <string>
#include <cstdint>
#include <libadb/types/nullable.hpp>
#include <libadb/types/time.hpp>
#include <libadb/api/guild/data/guild-scheduled-event-privacy-level.hpp>
#include <libadb/api/guild/data/guild-scheduled-event-status.hpp>
#include <libadb/api/guild/data/guild-scheduled-event-entity-type.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/resource/image.hpp>

namespace adb::api
{
    /**
     * @brief Guild Scheduled Event
     * @details https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object
     */
    struct GuildScheduledEvent
    {
        /// the id of the scheduled event
        adb::types::SFID id;
        /// the guild id which the scheduled event belongs to
        adb::types::SFID guildId;
        /// the channel id in which the scheduled event will be hosted, or null if scheduled entity type is EXTERNAL
        adb::types::Nullable<adb::types::SFID> channelId;
        /// the id of the user that created the scheduled event
        std::optional<adb::types::Nullable<adb::types::SFID>> creatorId;
        /// the name of the scheduled event (1-100 characters)
        std::string name;
        /// the description of the scheduled event (1-1000 characters)
        std::optional<adb::types::Nullable<std::string>> description;
        /// the time the scheduled event will start
        adb::types::TimePoint scheduledStartTime;
        /// the time the scheduled event will end, required if entity_type is EXTERNAL
        adb::types::Nullable<adb::types::TimePoint> scheduledEndTime;
        /// the privacy level of the scheduled event
        GuildScheduledEventPrivacyLevel privacyLevel;
        /// the status of the scheduled event
        GuildScheduledEventStatus status;
        /// the type of the scheduled event
        GuildScheduledEventEntityType entityType;
        /// the id of an entity associated with a guild scheduled event
        adb::types::Nullable<adb::types::SFID> entityId;
        /// the user that created the scheduled event
        std::optional<User> creator;
        /// the number of users subscribed to the scheduled event
        std::optional<int64_t> userCount;
        /// the cover image hash of the scheduled event
        std::optional<adb::resource::Image> image;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildScheduledEvent& event);
    LIBADB_API void from_json(const nlohmann::json& j, GuildScheduledEvent& event);
}