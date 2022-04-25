#pragma once

#include <libadb/libadb.hpp>
#include <string>

namespace adb::api
{
    /**
     * @brief Rate Limit Scope
     * @details https://discord.com/developers/docs/topics/rate-limits#header-format
     */
    enum class RateLimitScope
    {
        /// per bot or user limit
        User,
        /// per bot or user global limit
        Global,
        /// per resource limit
        Shared
    };

    LIBADB_API void from_string(const std::string &str, RateLimitScope &limit);
    LIBADB_API std::string to_string(RateLimitScope limit);
}