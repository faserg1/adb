#pragma once

#include <libadb/api/gateway/data/intents.hpp>
#include <libadb/api/utils/awaitable-event.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json_fwd.hpp>
#include <thread>
#include <memory>
#include <atomic>
#include <string>

namespace adb::api
{
    class Gateway;
    struct Payload;
    struct Dispatch;
    struct Ready;

    using WebSocketOpcode = websocketpp::frame::opcode::value;
    using WebSocketError = websocketpp::lib::error_code;
    using WebSocketClientType = websocketpp::config::asio_tls_client;
    using WebSocketClient = websocketpp::client<WebSocketClientType>;
    using WebSocketConnection = websocketpp::connection<WebSocketClientType>;
    using WebSocketConnectionPtr = std::shared_ptr<WebSocketConnection>;
    using SSLContextPtr = std::shared_ptr<boost::asio::ssl::context>;

    class GatewayController
    {
        struct FSMData;
    public:
        using DispatchCallback = std::function<void (const Payload &)>;

        GatewayController(const std::string &gatewayUrl, const std::string &token, Intents requiredIntents);
        ~GatewayController();

        /* For gateway */

        bool send(const Payload &msg);
        void setDispatchFunction(DispatchCallback onDispatch);

        void start();
        void stop();
        void runUnlessStopped();

        Intents getIntents();

        /* For states */

        bool connect();
        void startWebSocket();
        void stopWebSocket();

        void onStop();

        void setHeartbeatInterval(uint64_t interval);
        void startHeartbeat();
        void stopHeartbeat();

        void identity();
        void saveSessionInfo(const Ready &ready);
        void resume();

        void scheduleUpdate();
    private:
        void configureClient();
        void configureMessageHandler();

        void onMessage(const Payload &payload);
        void handleMessage(const Payload &payload);
        bool sendInternal(const Payload &msg);
        
    private:
        std::unique_ptr<FSMData> fsm_;
        struct Connection
        {
            WebSocketClient client;
            WebSocketConnectionPtr connection;
            std::jthread runThread;
        } webSocket_;
        struct Heartbeat
        {
            std::jthread thread;
            uint64_t interval = 0;
            uint64_t sequence = 0;
            std::atomic<uint64_t> lostHearbeat = 0;
        } heartbeat_;

        AwaitableEvent onStop_;

        std::string sessionId_;
        const std::string gatewayUrl_;
        const std::string token_;
        const Intents requiredIntents_;

        DispatchCallback dispatchCallback_;
    };
}