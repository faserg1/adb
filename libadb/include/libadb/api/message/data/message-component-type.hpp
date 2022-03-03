#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Component Type
     * @details https://discord.com/developers/docs/interactions/message-components#component-object-component-types
     */
    enum MessageComponentType : uint32_t
    {
        ActionRow = 1,
        Button = 2,
        SelectMenu = 3
    };
}