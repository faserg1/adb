#pragma once

namespace adb::api
{
    /**
     * @brief Sticker Format Type
     * @details https://discord.com/developers/docs/resources/sticker#sticker-object-sticker-format-types
     */
    enum class StickerFormat
    {
        PNG = 1,
        APNG = 2,
        LOTTIE = 3
    };
}