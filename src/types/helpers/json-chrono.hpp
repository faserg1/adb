#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <chrono>
#include <cstdio>

#include "chrono-helper.hpp"

namespace nlohmann
{
    template <typename ClockType>
    struct adl_serializer<std::chrono::time_point<ClockType>>
    {
        // Template 2017-07-11T17:27:07.299000+00:00

        static void to_json(json& j, const std::chrono::time_point<ClockType> &time)
        {
            
        }

        static void from_json(const json& j, std::chrono::time_point<ClockType> &time)
        {
            using TimePoint = std::chrono::time_point<ClockType>;
            using Duration = std::chrono::time_point<ClockType>::duration;
            using namespace std::chrono;

            auto strTime = j.get<std::string>();
            auto isoTime = adb::types::parseTime(strTime);
            
            if (!isoTime.has_value())
                return;
            auto isoTimeVal = isoTime.value();
            if (isoTimeVal.day.has_value())
                time = TimePoint(date::sys_days{date::year_month_day(isoTimeVal.year, isoTimeVal.month.value(), isoTimeVal.day.value())});
            else if (isoTimeVal.month.has_value())
            {
                time = TimePoint(date::sys_days{date::year_month_day(isoTimeVal.year, isoTimeVal.month.value(), date::day(0))});
                return;
            }
            else
            {
                time = TimePoint(date::sys_days{date::year_month_day(isoTimeVal.year, date::month(0), date::day(0))});
                return;
            }
            if (!isoTimeVal.hours.has_value())
                return;
            time += isoTimeVal.hours.value();
            if (!isoTimeVal.minutes.has_value())
                return;
            time += isoTimeVal.minutes.value();
            if (!isoTimeVal.seconds.has_value())
                return;
            time += isoTimeVal.seconds.value();
            if (isoTimeVal.milliseconds.has_value())
                time += isoTimeVal.milliseconds.value();
            if (isoTimeVal.microseconds.has_value())
                time += isoTimeVal.microseconds.value();
        }
    };
}