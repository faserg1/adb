#pragma once

#include <cstdint>
#include <libadb/types/helpers/enums.hpp>

namespace adb::api
{
    /**
     * @brief Gateway Intents
     * @details https://discord.com/developers/docs/topics/gateway#gateway-intents
     */
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

    ADB_ENUM_FLAGS_OPERATORS(Intent, Intents, uint64_t)

    constexpr const Intents AllIntents = 0 | 
        Intent::Guilds |
        Intent::GuildMembers |
        Intent::GuildBans |
        Intent::GuildEmojiAndStickers |
        Intent::GuildIntegrations |
        Intent::GuildWebhooks |
        Intent::GuildInvites |
        Intent::GuildVoiceStates |
        Intent::GuildPresences |
        Intent::GuildMessages |
        Intent::GuildMessageReactions |
        Intent::GuildMessageTyping |
        Intent::DirectMessages |
        Intent::DirectMessageReactions |
        Intent::DirectMessageTyping |
        Intent::GuildShelduleEvent;
}