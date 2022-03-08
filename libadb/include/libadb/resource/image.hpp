#pragma once

#include <libadb/libadb.hpp>
#include <libadb/resource/image-format.hpp>
#include <string>
#include <vector>
#include <future>
#include <cstddef>


namespace adb::resource
{
    class ImageResolver;

    class Image
    {
        friend ImageResolver;
    public:
        /**
         * @brief Get image name/hash
         */
        LIBADB_API std::string getName() const;
        /**
         * @brief Returns is format supported for this image
         */
        LIBADB_API bool isSupported(ImageFormat format) const;
        /**
         * @brief Get the Supported Formats for this image
         */
        LIBADB_API std::vector<ImageFormat> getSupportedFormats() const;
        /**
         * @brief Get the Image data of desired format
         * 
         * @param format Desired format 
         * @param size The size of image in power of 2, between 16 and 4096, if ommited, used default one
         * @return The future object with image data, throws, if format not supported
         */
        LIBADB_API std::future<std::vector<std::byte>> getImage(ImageFormat format, size_t size = 0) const;
    private:
        Image(std::vector<ImageFormat> supportedFormats, std::string path, std::string name, bool aForGif = false);
    private:
        const std::vector<ImageFormat> formats_;
        const std::string path_;
        const std::string name_;
        const bool aForGif_;
        /// https://discord.com/developers/docs/reference#image-formatting-image-base-url
        static const std::string cdnBase_;
    };
}