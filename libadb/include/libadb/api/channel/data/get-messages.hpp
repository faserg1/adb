#pragma once

#include <libadb/types/snowflake.hpp>
#include <optional>

namespace adb::api
{
    enum class GetMessagesOptType
    {
        Around,
        Before,
        After,
    };

    struct GetMessagesOpt
    {
        GetMessagesOptType type;
        adb::types::SFID messageId;
    };
}