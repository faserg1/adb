#pragma once

namespace adb::api
{
    /**
     * @brief Guild NSFW Level
     * @details https://discord.com/developers/docs/resources/guild#guild-object-guild-nsfw-level
     */
    enum class GuildNSFWLevel
    {
        DEFAULT = 0,
        EXPLICIT = 1,
        SAFE = 2,
        AGE_RESTRICTED = 3,
    };
}