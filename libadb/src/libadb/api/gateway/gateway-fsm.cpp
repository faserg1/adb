#include <libadb/api/gateway/gateway-fsm.hpp>
#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/event.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/ready.hpp>
using namespace adb::api;

namespace adb::api
{
    /* Main states */

    auto sConnected = boost::sml::state<class Connected>;
    auto sDisconnected = boost::sml::state<class Disconnected>;

    /* Inner Head States */

    auto sConnecting = boost::sml::state<class Connecting>;
    auto sReconnecting = boost::sml::state<class Reconnecting>;
    auto sDisconnecting = boost::sml::state<class Disconnecting>;

    /* Inner States */

    auto sWebSocketOpen = boost::sml::state<class WebSocketOpen>;
    auto sWebSocketStop = boost::sml::state<class WebSocketStop>;
    auto sHeartbeatStart = boost::sml::state<class HeartbeatStart>;
    auto sHeartbeatStop = boost::sml::state<class HeartbeatStop>;
    auto sHandshake = boost::sml::state<class Handshake>;
    auto sAuth = boost::sml::state<class Auth>;
    auto sResuming = boost::sml::state<class Resuming>;

    /* Events */

    struct RequestConnectEvent {};
    struct RequestDisconnectEvent {};
    struct WebSocketOpenEvent {};
    struct WebSocketCloseEvent {};
    struct WebSocketFailEvent {};
    struct LostHeartbeatEvent {};

    const auto connectGuard = [](GatewayController *controller)
    {
        return controller->connect();
    };

    const auto webSocketStart = [](GatewayController *controller)
    {
        controller->startWebSocket();
    };

    const auto heartbeatStart = [](GatewayController *controller)
    {
        controller->startHeartbeat();
    };

    const auto tryAuth = [](GatewayController *controller)
    {
        controller->identity();
    };

    const auto onHello = [](GatewayController *controller, const Hello &hello)
    {
        controller->setHeartbeatInterval(hello.heartbeatInterval);
    };

    const auto onReady = [](GatewayController *controller, const Ready &ready)
    {
        controller->saveSessionInfo(ready);
    };

    class StateMachineImpl
    {
    public:
        auto operator()()
        {
            using namespace boost::sml;

            return make_transition_table
            (
                *sDisconnected + event<RequestConnectEvent> [connectGuard] / webSocketStart = sConnecting,
                sConnecting + event<WebSocketOpenEvent> = sWebSocketOpen,
                sWebSocketOpen + event<Hello> / (onHello, heartbeatStart, tryAuth) = sHandshake,
                sHandshake + event<Ready> / onReady = sConnected
            );
        }
    };

    class StateMachine
    {
    public:
        StateMachine(GatewayController *controller) : machine(controller) {}
        boost::sml::sm<StateMachineImpl> machine;
    };

    std::shared_ptr<StateMachine> createStateMachine(GatewayController *controller)
    {
        return std::shared_ptr<StateMachine>(new StateMachine(controller), [](auto *ptr) {delete ptr;});
    }

    void processPayload(std::shared_ptr<StateMachine> machine, const Payload &payload);
    void processDispatch(std::shared_ptr<StateMachine> machine, const Payload &payload);

    void processEvent(std::shared_ptr<StateMachine> machine, StateMachineEventType event, const Payload *payload)
    {
        switch (event)
        {
        case StateMachineEventType::RequestConnect:
            machine->machine.process_event(RequestConnectEvent{});
            break;
        case StateMachineEventType::RequestDisconnect:
            machine->machine.process_event(RequestDisconnectEvent{});
            break;
        case StateMachineEventType::WebSocketOpen:
            machine->machine.process_event(WebSocketOpenEvent{});
            break;
        case StateMachineEventType::WebSocketClose:
            machine->machine.process_event(WebSocketCloseEvent{});
            break;
        case StateMachineEventType::WebSocketFail:
            machine->machine.process_event(WebSocketFailEvent{});
            break;
        case StateMachineEventType::LostHeartbeat:
            machine->machine.process_event(LostHeartbeatEvent{});
            break;
        case StateMachineEventType::Payload:
            if (!payload)
                return;
            processPayload(machine, *payload);
            break;
        default:
            break;
        }
        
    }

    void processPayload(std::shared_ptr<StateMachine> machine, const Payload &payload)
    {
        switch (payload.op)
        {
        case GatewayOpCode::Hello:
        {
            auto hello = payload.data.get<Hello>();
            machine->machine.process_event(hello);
        }
        case GatewayOpCode::Dispatch:
            if (payload.eventName.has_value())
                processDispatch(machine, payload);
            break;
        }
    }

    void processDispatch(std::shared_ptr<StateMachine> machine, const Payload &payload)
    {
        auto event = from_string(payload.eventName.value());
        switch (event)
        {
        case Event::READY:
        {
            auto ready = payload.data.get<Ready>();
            machine->machine.process_event(ready);
            break;
        }
        default:
            break;
        }
    }

}