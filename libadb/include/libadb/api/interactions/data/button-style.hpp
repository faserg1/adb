#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Button Style
     * @details https://discord.com/developers/docs/interactions/message-components#button-object-button-styles
     */
    enum class ButtonStyle : uint32_t
    {
        Primary = 1,
        Secondary = 2,
        Success = 3,
        Danger = 4,
        Link = 5
    };
}