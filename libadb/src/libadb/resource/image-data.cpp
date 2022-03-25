#include <libadb/resource/image-data.hpp>
#include <libadb/encoding/base64.hpp>
#include <stdexcept>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
using namespace adb::resource;

std::string adb::resource::to_string(const ImageData &data)
{
    std::string mimeType;
    switch (data.format)
    {
        case ImageFormat::JPEG:
            mimeType = "image/jpeg";
            break;
        case ImageFormat::GIF:
            mimeType = "image/gif";
            break;
        case ImageFormat::PNG:
            mimeType = "image/png";
            break;
        default:
            throw std::runtime_error("Ivalid format for image data!");
            return {};
    }
    return fmt::format("data:{};base64,{}", mimeType, adb::encoding::encode(data.data));
}

void adb::resource::from_string(const std::string &input, ImageData &data)
{
    // todo? 
}

void adb::resource::to_json(nlohmann::json& j, const ImageData& data)
{
    j = to_string(data);
}

void adb::resource::from_json(const nlohmann::json& j, ImageData& data)
{
    auto str = j.get<std::string>();
    from_string(str, data);
}