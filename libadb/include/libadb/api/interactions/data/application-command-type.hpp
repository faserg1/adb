#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Application Command Types
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
     */
    enum class ApplicationCommandType : uint32_t
    {
        CHAT_INPUT = 1,
        USER = 2,
        MESSAGE = 3
    };
}