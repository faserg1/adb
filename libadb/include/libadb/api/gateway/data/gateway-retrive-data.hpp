#pragma once

#include <string>
#include <cstdint>

namespace adb::api
{
    class DiscordApi;

    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/gateway#get-gateway-example-response
     */
    struct GatewayRetriveData
    {
        std::string url;
    };

    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/gateway#session-start-limit-object
     */
    struct GatewayBotSessionStartLimit
    {
        uint64_t total;
        uint64_t remaining;
        uint64_t resetAfter;
        uint64_t maxConcurrency;
    };

    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/gateway#get-gateway-bot-json-response
     */
    struct GatewayBotRetriveData
    {
        std::string url;
        uint64_t shards;
        GatewayBotSessionStartLimit sessionStartLimit;
    };
}