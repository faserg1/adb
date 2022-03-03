#pragma once

#include <cstdint>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Gateway "Hello" structure
     * @details https://discord.com/developers/docs/topics/gateway#connecting-example-gateway-hello
     */
    struct Hello
    {
        /// The heartbeat interval in milliseconds
        uint64_t heartbeatInterval;
    };

    void to_json(nlohmann::json& j, const Hello& hello);
    void from_json(const nlohmann::json& j, Hello& hello);
}