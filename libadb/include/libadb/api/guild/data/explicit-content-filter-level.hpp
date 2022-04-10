#pragma once

namespace adb::api
{
    /**
     * @brief Explicit Content Filter Level
     * @details https://discord.com/developers/docs/resources/guild#guild-object-explicit-content-filter-level
     */
    enum class ExplicitContentFilterLevel
    {
        /// media content will not be scanned
        DISABLED = 0,
        /// media content sent by members without roles will be scanned
        MEMBERS_WITHOUT_ROLES = 1,
        /// media content sent by all members will be scanned
        ALL_MEMBERS = 2
    };
}