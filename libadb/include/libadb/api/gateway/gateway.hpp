#pragma once

#include <string>
#include <memory>
#include <functional>
#include <libadb/api/gateway/data/intents.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class Context;
    class DiscordApi;
    class GatewayEvents;
    class GatewayController;

    struct Payload;
    struct Dispatch;

    /**
     * @brief Gateway will receive events from Discord via WebSocket
     * @details https://discord.com/developers/docs/topics/gateway
     */
    class Gateway
    {
        friend DiscordApi;
        friend GatewayController;
    public:
        LIBADB_API ~Gateway();

        LIBADB_API void start();
        LIBADB_API void stop();

        LIBADB_API void runUnlessStopped();

        LIBADB_API bool send(const Payload &msg);

        LIBADB_API Intents getIntents();

        LIBADB_API std::shared_ptr<GatewayEvents> events() const;
    protected:
        virtual void onMessage(const Payload &msg);
        virtual void onDispatch(const Dispatch &dispatch);
        virtual void onDispatchUnknown(const std::string &eventName, const nlohmann::json &data);
    private:
        Gateway(std::shared_ptr<Context> context, const std::string &gatewayUrl, Intents requiredIntents);
    private:
        const std::shared_ptr<Context> context_;
        
        std::unique_ptr<GatewayController> controller_;
        std::shared_ptr<GatewayEvents> events_;
    };
}