#include <libadb/resource/image-format.hpp>
#include <stdexcept>
using namespace adb::resource;

std::string adb::resource::getExtension(ImageFormat format)
{
    switch (format)
    {
        case ImageFormat::JPEG:
            return ".jpg";
        case ImageFormat::PNG:
            return ".png";
        case ImageFormat::WebP:
            return ".webp";
        case ImageFormat::GIF:
            return ".gif";
        case ImageFormat::Lottie:
            return ".json";
        default:
            throw std::runtime_error("Unknown image format");
    }
}