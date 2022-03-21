#pragma once

namespace adb::api
{
    /**
     * @brief Text Input Style
     * @details https://discord.com/developers/docs/interactions/message-components#text-inputs-text-input-styles
     */
    enum class TextInputStyle
    {
        /// A single-line input
        Short = 1,
        /// A multi-line input
        Paragraph = 2,
    };
}