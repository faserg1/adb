#pragma once

#include <libadb/types/helpers/enums.hpp>
#include <cstdint>

namespace adb::api
{
    /**
     * @brief Application Flags
     * @details https://discord.com/developers/docs/resources/application#application-object-application-flags
     */
    enum class ApplicationFlag : uint64_t
    {
        /// Intent required for bots in 100 or more servers to receive presence_update events
        GATEWAY_PRESENCE = (1 << 12),
        /// Intent required for bots in under 100 servers to receive presence_update events, found in Bot Settings
        GATEWAY_PRESENCE_LIMITED = (1 << 13),
        /// Intent required for bots in 100 or more servers to receive member-related events like guild_member_add
        GATEWAY_GUILD_MEMBERS = (1 << 14),
        /// Intent required for bots in under 100 servers to receive member-related events like guild_member_add, found in Bot Settings
        GATEWAY_GUILD_MEMBERS_LIMITED = (1 << 15),
        /// Indicates unusual growth of an app that prevents verification
        VERIFICATION_PENDING_GUILD_LIMIT = (1 << 16),
        /// Indicates if an app is embedded within the Discord client (currently unavailable publicly)
        EMBEDDED = (1 << 17),
        /// Intent required for bots in 100 or more servers to receive message content
        GATEWAY_MESSAGE_CONTENT = (1 << 18),
        /// Intent required for bots in under 100 servers to receive message content, found in Bot Settings
        GATEWAY_MESSAGE_CONTENT_LIMITED = (1 << 19)
    };

    ADB_ENUM_FLAGS_OPERATORS(ApplicationFlag, ApplicationFlags, uint64_t)
}