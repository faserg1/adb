#pragma once

#include <string>
#include <memory>
#include <functional>
#include <libadb/api/gateway/data/intents.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    class DiscordApi;
    class GatewayEvents;

    struct Payload;
    struct Dispatch;

    /**
     * @brief Gateway will receive events from Discord via WebSocket
     * @details https://discord.com/developers/docs/topics/gateway
     */
    class Gateway
    {
        friend DiscordApi;
        struct GatewayData;
    public:
        ~Gateway();

        bool connect();
        void run();
        bool send(const Payload &msg);

        Intents getIntents() { return requiredIntents_; }

        std::shared_ptr<GatewayEvents> events() const;
    protected:
        virtual void onMessage(const Payload &msg);
        virtual void onDispatch(const Dispatch &dispatch);

        bool sendInternal(const Payload &msg);
    private:
        Gateway(const std::string &gatewayUrl, Intents requiredIntents);

        void configureClient();
        void configureMessageHandler();

        void startHeartbeat(uint64_t intervalms);
        void stopHeartbeat();

        void identify();
    private:
        const std::string gatewayUrl_;
        std::unique_ptr<GatewayData> data_;
        std::shared_ptr<GatewayEvents> events_;

        Intents requiredIntents_;
    };
}