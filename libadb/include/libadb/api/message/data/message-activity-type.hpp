#pragma once

namespace adb::api
{
    /**
     * @brief Message Activity Type
     * @details https://discord.com/developers/docs/resources/channel#message-object-message-activity-types
     */
    enum class MessageActivityType
    {
        JOIN = 1,
        SPECTATE = 2,
        LISTEN = 3,
        JOIN_REQUEST = 4
    };
}