#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Interaction Type
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-type
     */
    enum class InteractionType : uint32_t
    {
        PING = 1,
        APPLICATION_COMMAND = 2,
        MESSAGE_COMPONENT = 3,
        APPLICATION_COMMAND_AUTOCOMPLETE = 4,
        MODAL_SUBMIT = 5
    };

    /** 
     * @brief Interaction Callback Type
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-type
     */
    enum class InteractionCallbackType : uint32_t
    {
        /// ACK a Ping (can be used in response to message components interactions)
        PONG = 1,
        CHANNEL_MESSAGE_WITH_SOURCE = 4,
        DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5,
        DEFERRED_UPDATE_MESSAGE = 6,
        UPDATE_MESSAGE = 7,
        APPLICATION_COMMAND_AUTOCOMPLETE_RESULT = 8,
        MODAL = 9
    };
}
