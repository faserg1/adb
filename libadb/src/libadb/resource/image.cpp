#include <libadb/resource/image.hpp>
#include <cpr/cpr.h>
#include <fmt/format.h>
#include <stdexcept>
#include <algorithm>
using namespace adb::resource;

const std::string Image::cdnBase_ = "https://cdn.discordapp.com/";

Image::Image(std::vector<ImageFormat> supportedFormats, std::string path, std::string name, bool aForGif) :
    formats_(supportedFormats), path_(path), name_(name), aForGif_(aForGif)
{

}

std::string Image::getName() const
{
    return name_;
}

bool Image::isSupported(ImageFormat format) const
{
    return std::find(formats_.begin(), formats_.end(), format) != formats_.end();   
}

std::vector<ImageFormat> Image::getSupportedFormats() const
{
    return formats_;
}

std::future<std::vector<std::byte>> Image::getImage(ImageFormat format, size_t size) const
{
    if (!isSupported(format))
        throw std::runtime_error("Image format not supported");
    // Image size can be any power of two between 16 and 4096.
    if (size && ((size & (size - 1)) != 0 || size < 16 || size > 4096))
        throw std::runtime_error("Size should be power of 2, between 16 adn 4096");
    auto extension = getExtension(format);
    std::string name;
    // In the case of endpoints that support GIFs, the hash will begin with a_ if it is available in GIF format.
    // (example: a_1269e74af4df7417b13759eae50c83dc)
    if (format == ImageFormat::GIF && aForGif_)
        name = "a_" + name_;
    else
        name = name_;
    // The returned size can be changed by appending a querystring of ?size=desired_size to the URL.
    auto querySize = size ? fmt::format("?size={}", size) : "";
    auto url = fmt::format("{}{}{}{}{}", cdnBase_, path_, name, extension, querySize);
    return std::async(std::launch::async, [url]() -> std::vector<std::byte>
    {
        auto session = cpr::Session();
        session.SetUrl(cpr::Url{url});
        auto response = session.Get();
        if (response.error.code != cpr::ErrorCode::OK)
            throw response.error;
        if (response.status_code < 200 || response.status_code >= 300)
            throw std::runtime_error(response.status_line);
        std::vector<std::byte> result(response.text.size());
        memcpy(result.data(), response.text.data(), response.text.size());
        return result;
    });
}