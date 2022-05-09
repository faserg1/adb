#include <libadb/api/gateway/gateway-fsm.hpp>
#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/event.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/ready.hpp>
#include <iostream>
#include <queue>
#include <fmt/format.h>
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
    struct HeartbeatStopEvent {};
    
    struct ReconnectEvent {};
    struct ResumedEvent {};

    struct ConnectingDone {};
    struct ReconnectingDone {};
    struct DisconnectingDone {};

    const auto webSocketConnect = [](GatewayController *controller)
    {
        controller->connect();
    };

    const auto webSocketStart = [](GatewayController *controller)
    {
        controller->startWebSocket();
    };

    const auto webSocketStop = [](GatewayController *controller)
    {
        controller->stopWebSocket();
    };

    const auto webSocketOpenedGuard = [](GatewayController *controller) -> bool
    {
        return controller->isWebSocketOpened();
    };

    const auto webSocketClosedGuard = [](GatewayController *controller) -> bool
    {
        return !controller->isWebSocketOpened();
    };

    const auto heartbeatStart = [](GatewayController *controller)
    {
        controller->startHeartbeat();
    };

    const auto heartbeatStop = [](GatewayController *controller)
    {
        controller->stopHeartbeat();
    };

    const auto tryAuth = [](GatewayController *controller)
    {
        controller->identity();
    };

    const auto tryResume = [](GatewayController *controller)
    {
        controller->resume();
    };

    const auto onHello = [](GatewayController *controller, const Hello &hello)
    {
        controller->setHeartbeatInterval(hello.heartbeatInterval);
    };

    const auto onReady = [](GatewayController *controller, const Ready &ready)
    {
        controller->saveSessionInfo(ready);
    };

    class StateCompositeConnecting
    {
    public:
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                sConnecting + on_entry<_> / (webSocketConnect, webSocketStart),
                *sConnecting + event<WebSocketOpenEvent> = sWebSocketOpen,
                sWebSocketOpen + event<Hello> / (onHello, heartbeatStart, tryAuth) = sHandshake,
                sHandshake + event<Ready> / (onReady) = X,
                X + on_entry<_> / process(ConnectingDone{})
            );
        }
    };

    class StateCompositeReconnecting
    {
    public:
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                sReconnecting + on_entry<_> / (heartbeatStop, webSocketStop),
                *sReconnecting + event<WebSocketCloseEvent> [webSocketOpenedGuard] = sWebSocketStop,
                sReconnecting [webSocketClosedGuard] = sWebSocketStop,
                sWebSocketStop + on_entry<_> / (webSocketStart),
                sWebSocketStop + event<WebSocketOpenEvent> = sWebSocketOpen,
                sWebSocketOpen + event<Hello> / (onHello, heartbeatStart, tryResume) = sHandshake,
                sHandshake + event<ResumedEvent> = X,
                X + on_entry<_> / process(ReconnectingDone{})
            );
        }
    };

    class StateCompositeDisconnecting
    {
    public:
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                sDisconnecting + on_entry<_> / (heartbeatStop, webSocketStop),
                *sDisconnecting + event<WebSocketCloseEvent> [webSocketOpenedGuard] = X,
                sDisconnecting [webSocketClosedGuard] = X,
                X + on_entry<_> / process(DisconnectingDone{})
            );
        }
    };

    class StateMachineImpl
    {
    public:
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                *sDisconnected + event<RequestConnectEvent> = state<StateCompositeConnecting>,
                state<StateCompositeConnecting> + event<ConnectingDone> = sConnected,
                sConnected + event<ReconnectEvent> = state<StateCompositeReconnecting>,
                sConnected + event<WebSocketCloseEvent> = state<StateCompositeReconnecting>,
                state<StateCompositeReconnecting> + event<ReconnectingDone> = sConnected,
                sConnected + event<RequestDisconnectEvent> = state<StateCompositeDisconnecting>,
                state<StateCompositeDisconnecting> + event<DisconnectingDone> = sDisconnected
            );
        }
    };

    class StateMachine
    {
        struct my_logger {
            template <class SM, class TEvent>
            void log_process_event(const TEvent&) {
                std::cout << fmt::format("[{}][process_event] {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TEvent>()) << std::endl;
            }

            template <class SM, class TGuard, class TEvent>
            void log_guard(const TGuard&, const TEvent&, bool result) {
                std::cout << fmt::format("[{}][guard] {} {} {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TGuard>(),
                    boost::sml::aux::get_type_name<TEvent>(), (result ? "[OK]" : "[Reject]")) << std::endl;
            }

            template <class SM, class TAction, class TEvent>
            void log_action(const TAction&, const TEvent&) {
                std::cout << fmt::format("[{}][action] {} {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TAction>(),
                    boost::sml::aux::get_type_name<TEvent>()) << std::endl;
            }

            template <class SM, class TSrcState, class TDstState>
            void log_state_change(const TSrcState& src, const TDstState& dst) {
                std::cout << fmt::format("[{}][transition] {} -> {}",
                    boost::sml::aux::get_type_name<SM>(), src.c_str(), dst.c_str()) << std::endl;
            }
        };
    public:
        StateMachine(GatewayController *controller) : machine(controller, my_logger{}) {}
        boost::sml::sm<StateMachineImpl, boost::sml::logger<my_logger>, boost::sml::process_queue<std::queue>> machine;
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
            break;
        }
        case GatewayOpCode::Reconnect:
        {
            machine->machine.process_event(ReconnectEvent{});
            break;
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
        case Event::RECONNECT:
        {
            machine->machine.process_event(ReconnectEvent{});
            break;
        }
        case Event::RESUMED:
        {
            machine->machine.process_event(ResumedEvent{});
            break;
        }
        default:
            break;
        }
    }

}
