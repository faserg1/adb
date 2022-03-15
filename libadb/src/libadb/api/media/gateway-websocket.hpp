#pragma once

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <cstdint>
#include <libadb/types/snowflake.hpp>

namespace adb::api
{
    namespace WebSocketCloseCode = websocketpp::close::status;

    struct MediaPayload;

    class GatewayMediaWebSocket
    {
        using WebSocketOpcode = websocketpp::frame::opcode::value;
        using WebSocketError = websocketpp::lib::error_code;
        using WebSocketClientType = websocketpp::config::asio_tls_client;
        using WebSocketClient = websocketpp::client<WebSocketClientType>;
        using WebSocketConnection = websocketpp::connection<WebSocketClientType>;
        using WebSocketConnectionPtr = std::shared_ptr<WebSocketConnection>;
        using SSLContextPtr = std::shared_ptr<boost::asio::ssl::context>;

    public:
        GatewayMediaWebSocket(adb::types::SFID guildId, adb::types::SFID userId);

        using MessageHandler = std::function<void(const MediaPayload &)>;

        void setMessageHandler(MessageHandler handler);
        bool sendMessage(const MediaPayload &payload);

        [[nodiscard]] std::future<bool> connect(adb::types::SFID channelId, std::string endpoint, std::string session, std::string token);
        [[nodiscard]] std::future<void> disconnect();

        bool isConnected() const;
        adb::types::SFID getChannelId() const;

        std::vector<std::string> getAwailableModes() const;

    protected:
        virtual void initClient();
        virtual void configureWebsocketHandlers();

        virtual void onHearbeatStart();
        virtual void onHeartbeatStop();
        virtual void onHearbeatDead();

        void log(std::string msg);

    private:
        void internalOnMessage(const MediaPayload &payload);
        bool internalSendMessage(const MediaPayload &payload);

        void internalHandleMessage(const MediaPayload &payload);

        std::future<bool> internalConnect();
        std::future<void> internalDisconnect();

        void identity();

        void internalWebsocketWorker();
        void internalHeartBeatWorker(std::stop_token stop);

        std::future<bool> startHeartbeat();
        std::future<bool> stopHeartbeat();

    protected:
        const adb::types::SFID guildId_;
        const adb::types::SFID userId_;

        adb::types::SFID channelId_;
        std::string endpoint_;
        std::string gatewayUrl_;
        std::string sessionId_;
        std::string token_;

        std::vector<std::string> modes_;

        MessageHandler handler_;
        WebSocketClient client_;
        WebSocketConnectionPtr connection_;

    private:
        std::jthread heartbeatThread_;
        uint64_t heartbeatIntervalms_ = 0;
        uint64_t heartbeatNonce_ = 0;
        std::atomic<uint64_t> missedHeartBeats_ = 0;
        std::thread websocketThread_;

        std::atomic_bool connected_;
        std::atomic_flag connectionUpdated_;

        const size_t gatewayWebsocketVersion_ = 6;
    };
}