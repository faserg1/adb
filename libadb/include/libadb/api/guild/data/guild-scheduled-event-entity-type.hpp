#pragma once

namespace adb::api
{
    /**
     * @brief Guild Scheduled Event Entity Types
     * @details https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-entity-types
     */
    enum class GuildScheduledEventEntityType
    {
        STAGE_INSTANCE = 1,
        VOICE = 2,
        EXTERNAL = 3
    };
}