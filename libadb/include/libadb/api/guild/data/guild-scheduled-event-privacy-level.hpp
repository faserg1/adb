#pragma once

namespace adb::api
{
    /**
     * @brief Guild Scheduled Event Privacy Level
     * @details https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-privacy-level
     */
    enum class GuildScheduledEventPrivacyLevel
    {
        /// the scheduled event is only accessible to guild members
        GUILD_ONLY = 2,
    };
}