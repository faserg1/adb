#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Component Type
     * @details https://discord.com/developers/docs/interactions/message-components#component-object-component-types
     */
    enum class MessageComponentType : uint32_t
    {
        /// A container for other components
        ActionRow = 1,
        /// A button object
        Button = 2,
        /// A select menu for picking from choices
        SelectMenu = 3,
        /// A text input object
        TextInput = 4
    };
}