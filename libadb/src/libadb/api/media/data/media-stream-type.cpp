#include <libadb/api/media/data/media-stream-type.hpp>
#include <stdexcept>
using namespace adb::api;

std::string adb::api::to_string(MediaStreamType type)
{
    switch (type)
    {
    case MediaStreamType::Video:
        return "video";
    case MediaStreamType::Stream:
        return "stream";
    default:
        throw std::runtime_error("Unknown stream type!");
    }
}

void adb::api::from_string(const std::string &string, MediaStreamType &type)
{
    if (string == "video")
        type = MediaStreamType::Video;
    else if (string == "stream")
        type = MediaStreamType::Stream;
    else
        throw std::runtime_error("Unknown stream type!");
}