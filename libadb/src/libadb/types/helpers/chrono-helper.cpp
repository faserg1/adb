#include <libadb/types/helpers/chrono-helper.hpp>
#include <regex>
#include <fmt/format.h>
using namespace adb::types;

namespace
{
    static auto timeRegex = std::regex(
        "^(\\d{1,})-?(\\d{2})-?(\\d{2})(T(\\d{2}):?(\\d{2})?:?(\\d{2})?(.(\\d{6})|(\\d{3}))?)?((([+-])(\\d{2}):?(\\d{2}))|Z)?$",
        std::regex::ECMAScript | std::regex::optimize);

    enum class TimeRegexPos : int
    {
        Full = 0,
        Year = 1,
        Month = 2,
        Day = 3,
        // Unused
        TimeTotal = 4,
        Hours = 5,
        Minutes = 6,
        Seconds = 7,
        // Unused
        DotMicroMiliSeconds = 8,
        Microseconds = 9,
        Milliseconds = 10,
        TimeZoneTotal = 11,
        TimeZoneCustom = 12,
        TimeZoneSign = 13,
        TimeZoneDiffHours = 14,
        TimeZoneDiffMinutes = 15
    };
}

template <TimeRegexPos pos, class OutType>
void map_time(const std::smatch &match, std::optional<OutType> &out)
{
    constexpr auto iPos = static_cast<int>(pos);
    if (!match[iPos].matched)
    {
        out = std::nullopt;
        return;
    }
    out = OutType(std::stoul(match[iPos].str()));
}

std::optional<ISO8601Time> adb::types::parseTime(std::string txt)
{
    std::smatch m;
    std::regex_match(txt, m, timeRegex);
    if (m.empty())
        return std::nullopt;
    ISO8601Time time;
    time.year = date::year(std::stoi(m[static_cast<int>(TimeRegexPos::Year)]));
    map_time<TimeRegexPos::Month>(m, time.month);
    map_time<TimeRegexPos::Day>(m, time.day);
    map_time<TimeRegexPos::Hours>(m, time.hours);
    map_time<TimeRegexPos::Minutes>(m, time.minutes);
    map_time<TimeRegexPos::Seconds>(m, time.seconds);
    map_time<TimeRegexPos::Milliseconds>(m, time.milliseconds);
    map_time<TimeRegexPos::Microseconds>(m, time.microseconds);
    if (m[static_cast<int>(TimeRegexPos::TimeZoneCustom)].matched)
    {
        ISO8601Time::LocalZone lz;
        auto sign = m[static_cast<int>(TimeRegexPos::TimeZoneCustom)].str();
        if (sign == "-")
            lz.tzPlusUtc = true;
        else if (sign == "+")
            lz.tzPlusUtc = false;
        map_time<TimeRegexPos::TimeZoneDiffHours>(m, lz.hours);
        map_time<TimeRegexPos::TimeZoneDiffMinutes>(m, lz.minutes);
        time.localZone = lz;
    }
    return time;
}

std::string adb::types::formatTime(ISO8601Time time)
{
    // Template 2017-07-11T17:27:07.299000+00:00
    std::string totalTime;
    totalTime += fmt::format("{}", (int) time.year);
    if (!time.month.has_value())
        return totalTime;
    totalTime += fmt::format("-{}", (unsigned) time.month.value());
    if (!time.day.has_value())
        return totalTime;
    totalTime += fmt::format("-{}", (unsigned) time.day.value());
    if (!time.hours.has_value())
        return totalTime;
    totalTime += fmt::format("T{}", time.hours.value().count());
    if (!time.minutes.has_value())
        return totalTime;
    totalTime += fmt::format(":{}", time.minutes.value().count());
    if (!time.seconds.has_value())
        return totalTime;
    totalTime += fmt::format(":{}", time.seconds.value().count());
    return totalTime;
}