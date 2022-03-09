#pragma once

namespace adb::api
{
    /**
     * @brief Sticker Type
     * @details https://discord.com/developers/docs/resources/sticker#sticker-object-sticker-types
     */
    enum class StickerType
    {
        /// an official sticker in a pack, part of Nitro or in a removed purchasable pack
        STANDARD = 1,
        /// a sticker uploaded to a Boosted guild for the guild's members
        GUILD = 2,
    };
}