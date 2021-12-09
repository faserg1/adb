#include "msg-format.hpp"
#include <fmt/core.h>
using namespace adb::api;

std::string MsgFormat::mentionUser(adb::types::SFID userId)
{
    return fmt::format("<@{}>", (uint64_t) userId);
}

std::string MsgFormat::mentionNickname(adb::types::SFID userId)
{
    return fmt::format("<@!{}>", (uint64_t) userId);
}

std::string MsgFormat::mentionChannel(adb::types::SFID channelId)
{
    return fmt::format("<#{}>", (uint64_t) channelId);
}

std::string MsgFormat::mentionRole(adb::types::SFID roleId)
{
    return fmt::format("<@&{}>", (uint64_t) roleId);
}

std::string MsgFormat::customEmoji(std::string name, adb::types::SFID emojiId, bool animated)
{
    return fmt::format("<{}:{}:{}>", (animated ? "a" : ""), name, (uint64_t) emojiId);
}

std::string MsgFormat::timestamp(uint64_t secondsSinceEpoch, TimeStyle style)
{
    std::string_view svStyle;
    switch (style)
    {
    case TimeStyle::ShortTime:
        svStyle = "t";
        break;
    case TimeStyle::LongTime:
        svStyle = "T";
        break;
    case TimeStyle::ShortDate:
        svStyle = "d";
        break;
    case TimeStyle::LongDate:
        svStyle = "D";
        break;
    case TimeStyle::LongDateTime:
        svStyle = "F";
        break;
    case TimeStyle::RelativeTime:
        svStyle = "R";
        break;
    case TimeStyle::ShortDateTime:
    default:
        svStyle = "f";
        break;
    }
    return fmt::format("<t:{}:{}>", secondsSinceEpoch, svStyle);
}