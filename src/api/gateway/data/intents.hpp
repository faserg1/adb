#pragma once

#include <cstdint>

namespace adb::api
{
    enum class Intent : uint64_t
    {
        Guilds = (1 << 0),
        GuildMembers = (1 << 1),
        GuildBans = (1 << 2),
        GuildEmojiAndStickers = (1 << 3),
        GuildIntegrations = (1 << 4),
        GuildWebhooks = (1 << 5),
        GuildInvites = (1 << 6),
        GuildVoiceStates = (1 << 7),
        GuildPresences = (1 << 8),
        GuildMessages = (1 << 9),
        GuildMessageReactions = (1 << 10),
        GuildMessageTyping = (1 << 11),
        DirectMessages = (1 << 12),
        DirectMessageReactions = (1 << 13),
        DirectMessageTyping = (1 << 14),
        GuildShelduleEvent = (1 << 16)
    };

    using Intents = uint64_t;

    constexpr Intents operator+(Intent i)
    {
        return static_cast<uint64_t>(i);
    }

    constexpr Intents operator|(Intent i1, Intent i2)
    {
        return static_cast<uint64_t>(i1) | static_cast<uint64_t>(i2);
    }

    constexpr Intents operator|(Intents i1, Intent i2)
    {
        return i1 | static_cast<uint64_t>(i2);
    }
}