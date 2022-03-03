#pragma once

#include <chrono>

namespace adb::types
{
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

    template <class ClockType>
    struct DateTime
    {
        using TimeType = std::chrono::time_point<ClockType>;
        using Duration = TimeType::duration;
    public:
        enum class LocalDiffTime : char
        {
            PLUS = '+',
            MINUX = '-'
        };
        DateTime(TimeType t, LocalDiffTime dt, int hours, int minutes)
            : time(t), localDiff(std::chrono::hours(hours) + std::chrono::minutes(minutes))
        {

        }
        TimeType time;
        TimeType getLocalTime()
        {
            if (differenceType == LocalDiffTime::PLUS)
                return time + localDiff;
            else
                return time - localDiff;
        }
    private:
        Duration localDiff;
        LocalDiffTime differenceType;
    };
}