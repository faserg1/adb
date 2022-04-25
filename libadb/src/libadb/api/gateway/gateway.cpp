#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/context/context.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/identity.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/cfg/secrets.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <fmt/core.h>
#include <chrono>
#include <unordered_map>
using namespace adb::api;

using WebSocketOpcode = websocketpp::frame::opcode::value;
using WebSocketError = websocketpp::lib::error_code;
using WebSocketClientType = websocketpp::config::asio_tls_client;
using WebSocketClient = websocketpp::client<WebSocketClientType>;
using WebSocketConnection = websocketpp::connection<WebSocketClientType>;
using WebSocketConnectionPtr = std::shared_ptr<WebSocketConnection>;
using SSLContextPtr = std::shared_ptr<boost::asio::ssl::context>;


struct Gateway::GatewayData
{
    WebSocketClient client;
    WebSocketConnectionPtr connection;
    struct Heartbeat
    {
        std::jthread thread;
        uint64_t sequence;
    } heartbeat;
    
};

Gateway::Gateway(std::shared_ptr<Context> context, const std::string &gatewayUrl, Intents requiredIntents) :
    context_(context), gatewayUrl_(gatewayUrl),
    data_(std::make_unique<GatewayData>()), events_(GatewayEvents::create()), requiredIntents_(requiredIntents)
{
    configureClient();
    configureMessageHandler();
}

Gateway::~Gateway()
{
    stopHeartbeat();
}

bool Gateway::connect()
{
    WebSocketError ec;
    auto url = fmt::format("{}?v={}", gatewayUrl_, 9);
    WebSocketConnectionPtr con = data_->client.get_connection(gatewayUrl_, ec);
    if (ec)
    {
        auto msg = ec.message();
        return false;
    }
    data_->connection = data_->client.connect(con);
    return data_->connection && data_->connection->get_state() == websocketpp::session::state::open;
}

void Gateway::run()
{
    data_->client.run();
}

bool Gateway::send(const Payload &msg)
{
    return sendInternal(msg);
}

std::shared_ptr<GatewayEvents> Gateway::events() const
{
    return events_;
}

void Gateway::configureClient()
{
    data_->client.init_asio();
    data_->client.set_tls_init_handler([](auto conHandler) -> SSLContextPtr {
        SSLContextPtr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                         boost::asio::ssl::context::no_sslv2 |
                         boost::asio::ssl::context::no_sslv3 |
                         boost::asio::ssl::context::single_dh_use);
        return ctx;
    });
}

void Gateway::configureMessageHandler()
{
    data_->client.set_message_handler([this](auto conHandle, auto msg)
    {
        nlohmann::json obj = nlohmann::json::parse(msg->get_payload());
        auto payload = obj.get<adb::api::Payload>();
        onMessage(payload);
    });
}

void Gateway::onMessage(const Payload &msg)
{
    switch (msg.op)
    {
        case GatewayOpCode::Hello:
        {
            auto hello = msg.data.get<Hello>();
            startHeartbeat(hello.heartbeatInterval);
            identify();
            break;
        }
        case GatewayOpCode::HeartbeatACK:
            break;
        case GatewayOpCode::Dispatch:
        {
            auto eventType = from_string(msg.eventName.value());
            if (eventType != Event::UNKNOWN)
            {
                onDispatch({
                    .event = eventType,
                    .data = msg.data
                });
            }
            else
            {
                onDispatchUnknown(msg.eventName.value(), msg.data);
            }
            if (data_->heartbeat.sequence < msg.sequence.value_or(0))
                data_->heartbeat.sequence = msg.sequence.value();
            break;
        }
    }
}

void Gateway::onDispatch(const Dispatch &dispatch)
{
    events_->onDispatch(dispatch);
}

void Gateway::onDispatchUnknown(const std::string &eventName, const nlohmann::json &data)
{
    // TODO: 
}

bool Gateway::sendInternal(const Payload &msg)
{
    nlohmann::json jsObj = msg;
    WebSocketError ec;
    data_->client.send(data_->connection, jsObj.dump(), WebSocketOpcode::text, ec);
    if (ec)
    {
        auto msg = ec.message();
        return false;
    }
    return true;
}

void Gateway::startHeartbeat(uint64_t intervalms)
{
    data_->heartbeat.thread = std::jthread([this, intervalms](std::stop_token stop_token)
    {
        while (!stop_token.stop_requested())
        {
            sendInternal({
                .op = GatewayOpCode::Heartbeat,
                .data = nlohmann::json::parse("null")
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalms));
        }
    });
}

void Gateway::stopHeartbeat()
{
    if (data_->heartbeat.thread.joinable())
    {
        data_->heartbeat.thread.request_stop();
        data_->heartbeat.thread.join();
    }
}

void Gateway::identify()
{
    Identity identity {
        .token = context_->getSecrets().botToken,
        .properties = {
            .os = "linux",
            .browser = "adb",
            .device = "adb"
        },
        .intents = requiredIntents_,
    };
    sendInternal({
        .op = GatewayOpCode::Identify,
        .data = identity
    });
}