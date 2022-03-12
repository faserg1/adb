#pragma once

#include <libadb/libadb.hpp>
#include <string>

namespace adb::api
{
    /**
     * @brief 
     * 
     * [NOT DOCUMENTED!!]
     */
    enum class MediaStreamType
    {
        Video,
        Stream,
    };

    LIBADB_API std::string to_string(MediaStreamType type);
    LIBADB_API void from_string(const std::string &string, MediaStreamType &type);
}