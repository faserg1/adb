#pragma once

namespace adb::api
{
    /**
     * @brief Guild Scheduled Event Status
     * @details https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-status
     */
    enum class GuildScheduledEventStatus
    {
        SCHEDULED = 0,
        ACTIVE = 1,
        COMPLETED = 2,
        CANCELED = 3
    };
}