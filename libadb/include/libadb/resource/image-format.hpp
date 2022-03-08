#pragma once

#include <libadb/libadb.hpp>
#include <string>

namespace adb::resource
{
    /**
     * @brief Image Format
     * @details https://discord.com/developers/docs/reference#image-formatting-image-formats
     */
    enum class ImageFormat
    {
        /// .jpeg, .jpg
        JPEG,
        /// .png
        PNG,
        /// .webp
        WebP,
        /// .gif
        GIF,
        /// .json
        Lottie
    };

    LIBADB_API std::string getExtension(ImageFormat format);
}