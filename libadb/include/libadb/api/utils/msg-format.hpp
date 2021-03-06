#pragma once

#include <string>
#include <chrono>
#include <libadb/types/snowflake.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Message Formatting Utility
     * @details https://discord.com/developers/docs/reference#message-formatting
     */
    class MsgFormat
    {
    public:
        MsgFormat() = delete;

        /**
         * @brief Time Formatting Style
         * @details https://discord.com/developers/docs/reference#message-formatting-timestamp-styles
         */
        enum class TimeStyle
        {
            ShortTime,
            LongTime,
            ShortDate,
            LongDate,
            ShortDateTime,
            LongDateTime,
            RelativeTime
        };

        LIBADB_API static std::string mentionUser(adb::types::SFID userId);
        LIBADB_API static std::string mentionNickname(adb::types::SFID userId);
        LIBADB_API static std::string mentionChannel(adb::types::SFID channelId);
        LIBADB_API static std::string mentionRole(adb::types::SFID roleId);
        LIBADB_API static std::string customEmoji(std::string name, adb::types::SFID emojiId, bool animated = false);
        template <class ClockType>
        static std::string timestamp(std::chrono::time_point<ClockType> ts, TimeStyle style = TimeStyle::ShortDateTime)
        {
            return timestamp(std::chrono::duration_cast<std::chrono::seconds>(ts.time_since_epoch()).count(), style);
        }
        LIBADB_API static std::string timestamp(uint64_t secondsSinceEpoch, TimeStyle style = TimeStyle::ShortDateTime);
    };
}
