#pragma once

#include <cstdint>
#include <chrono>
#include <optional>
#include <date/date.h>

#include <libadb/libadb.hpp>

namespace adb::types
{
    struct ISO8601Time
    {
        date::year year;
        std::optional<date::month> month;
        std::optional<date::day> day;
        std::optional<std::chrono::hours> hours;
        std::optional<std::chrono::minutes> minutes;
        std::optional<std::chrono::seconds> seconds;
        std::optional<std::chrono::milliseconds> milliseconds;
        std::optional<std::chrono::microseconds> microseconds;

        struct LocalZone
        {
            // minus, if false
            bool tzPlusUtc = true;
            std::optional<std::chrono::hours> hours;
            std::optional<std::chrono::minutes> minutes;
        };
        std::optional<LocalZone> localZone;
    };

    LIBADB_API std::optional<ISO8601Time> parseTime(std::string time);
    LIBADB_API std::string formatTime(ISO8601Time time);
}