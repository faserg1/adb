#pragma once

#include <libadb/types/helpers/enums.hpp>
#include <cstdint>

namespace adb::api
{
    /**
     * @brief System Channel Flag
     * @details https://discord.com/developers/docs/resources/guild#guild-object-system-channel-flags
     */
    enum class SystemChannelFlag : uint16_t
    {
        /// Suppress member join notifications
        SUPPRESS_JOIN_NOTIFICATIONS = 1 << 0,
        /// Suppress server boost notifications
        SUPPRESS_PREMIUM_SUBSCRIPTIONS= 1 << 1,
        /// Suppress server setup tips
        SUPPRESS_GUILD_REMINDER_NOTIFICATIONS = 1 << 2,
        /// Hide member join sticker reply buttons
        SUPPRESS_JOIN_NOTIFICATION_REPLIES = 1 << 3,
    };

    ADB_ENUM_FLAGS_OPERATORS(SystemChannelFlag, SystemChannelFlags, uint16_t)
}