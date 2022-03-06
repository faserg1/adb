#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <libadb/api/gateway/data/gateway-retrive-data.hpp>
#include <libadb/api/gateway/data/retrive-query.hpp>

namespace adb::api
{
    class DiscordApi;

    class GatewayRetrive
    {
        friend DiscordApi;
    public:
        /**
         * @brief Get Gateway Bot
         * @details https://discord.com/developers/docs/topics/gateway#get-gateway-bot
         * @return GatewayBotRetriveData 
         */
        LIBADB_API GatewayBotRetriveData retriveBotGateway(std::optional<GatewayRetriveQuery> query);
    private:
        GatewayRetrive(const std::string &baseUrl);
    private:
        const std::string baseGatewayUrl_;
    };
}