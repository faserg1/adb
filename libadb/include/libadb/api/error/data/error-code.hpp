#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Along with the HTTP error code, our API can also return more detailed error codes through a code key in the JSON error response.
     * @details https://discord.com/developers/docs/topics/opcodes-and-status-codes#json
     */
    enum class ErrorCode : uint64_t
    {
        
    };
}