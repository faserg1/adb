#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Guild Scheduled Event Entity Metadata
     * @details https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-entity-metadata
     */
    struct GuildScheduledEventEntityMetadata
    {
        /// location of the event (1-100 characters)
        std::optional<std::string> location;
    };

    LIBADB_API void to_json(nlohmann::json& j, const GuildScheduledEventEntityMetadata& metadata);
    LIBADB_API void from_json(const nlohmann::json& j, GuildScheduledEventEntityMetadata& metadata);
}