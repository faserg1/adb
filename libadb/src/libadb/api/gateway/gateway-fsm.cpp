#include <libadb/api/gateway/gateway-fsm.hpp>
#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/event.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/ready.hpp>
#include <boost/sml.hpp>
#include <loguru/loguru.hpp>
#include <queue>
#include <thread>
#include <fmt/format.h>
using namespace adb::api;

namespace adb::api
{
    /* Main states */

    auto sConnected = boost::sml::state<struct Connected>;
    auto sDisconnected = boost::sml::state<struct Disconnected>;

    /* Inner Head States */

    struct Reconnecting
    {
        uint64_t attemt = 0;
        static const uint64_t maxAttempts = 5;
    };

    auto sConnecting = boost::sml::state<struct Connecting>;
    auto sReconnecting = boost::sml::state<struct Reconnecting>;
    auto sDisconnecting = boost::sml::state<struct Disconnecting>;

    /* Inner States */

    auto sWebSocketOpen = boost::sml::state<struct WebSocketOpen>;
    auto sWebSocketClose = boost::sml::state<struct WebSocketClose>;
    auto sWebSocketStop = boost::sml::state<struct WebSocketStop>;
    auto sHeartbeatStart = boost::sml::state<struct HeartbeatStart>;
    auto sHeartbeatStop = boost::sml::state<struct HeartbeatStop>;
    auto sHandshake = boost::sml::state<struct Handshake>;
    auto sAuth = boost::sml::state<struct Auth>;
    auto sResuming = boost::sml::state<struct Resuming>;

    /* Events */

    struct RequestConnectEvent {};
    struct RequestDisconnectEvent {};
    
    struct WebSocketOpenEvent {};
    struct WebSocketCloseEvent {};
    struct WebSocketStopEvent {};
    struct WebSocketFailEvent {};

    struct LostHeartbeatEvent {};
    struct HeartbeatStopEvent {};
    
    struct ReconnectEvent {};
    struct ResumedEvent {};
    struct InvalidSessionEvent {};

    struct ConnectingDone {};
    struct ConnectingFailed {};
    struct ReconnectingDone {};
    struct ReconnectingFailed {};
    struct DisconnectingDone {};

    /* WebSocket */

    const auto webSocketConnect = [](GatewayController *controller)
    {
        controller->connect();
    };

    const auto webSocketDisconnect = [](GatewayController *controller)
    {
        controller->disconnect();
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

    const auto webSocketStoppedGuard = [](GatewayController *controller) -> bool
    {
        return controller->isWebSocketStopped();
    };

    /* Heartbeat */

    const auto heartbeatStart = [](GatewayController *controller)
    {
        controller->startHeartbeat();
    };

    const auto heartbeatStop = [](GatewayController *controller)
    {
        controller->stopHeartbeat();
    };

    /* Ident */

    const auto tryAuth = [](GatewayController *controller)
    {
        controller->identity();
    };

    const auto tryAuthLater = [](GatewayController *controller)
    {
        std::thread([controller]
        {
            // wait 1-5 seconds, and then identify
            std::this_thread::sleep_for(std::chrono::seconds(3));
            controller->identity();
        }).detach();
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

    /* Misc */

    const auto doStop = [](GatewayController *controller)
    {
        controller->onStop();
    };

    /* Reconnect */

    const auto reconnectAttemptIncrement = [](Reconnecting &reconnecting)
    {
        reconnecting.attemt++;
    };

    const auto reconnectAttemptReset = [](Reconnecting &reconnecting)
    {
        reconnecting.attemt = 0;
    };

    const auto reconnectAttemptCheckGuard = [](Reconnecting &reconnecting) -> bool
    {
        return reconnecting.attemt < reconnecting.maxAttempts;
    };

    const auto reconnectAttemptCheckFail = [](Reconnecting &reconnecting)
    {
        LOG_F(ERROR, "To many reconnects ({})! Disconnecting.", reconnecting.attemt);
        reconnecting.attemt = 0;
    };

    class StateCompositeConnecting
    {
    public:
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                sConnecting + on_entry<_> / (webSocketStart, webSocketConnect),
                *sConnecting + event<WebSocketOpenEvent> = sWebSocketOpen,
                sWebSocketOpen + event<Hello> / (onHello, heartbeatStart, tryAuth) = sHandshake,
                sHandshake + event<Ready> / (onReady) = X,
                X + on_entry<_> [webSocketOpenedGuard] / process(ConnectingDone{}),
                state<_> + unexpected_event<WebSocketCloseEvent> / (process(ConnectingFailed{}), []{LOG_F(ERROR, "Connection failed!");}) = X,
                state<_> + unexpected_event<InvalidSessionEvent> / (process(ConnectingFailed{}), []{LOG_F(ERROR, "Connection failed!");}) = X
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
                *sReconnecting + on_entry<_> [reconnectAttemptCheckGuard] / (reconnectAttemptIncrement, heartbeatStop, webSocketDisconnect),
                sReconnecting [!reconnectAttemptCheckGuard] / (process(ReconnectingFailed{}), reconnectAttemptCheckFail) = X,
                sReconnecting + event<WebSocketCloseEvent> [!webSocketOpenedGuard] = sWebSocketClose,
                sReconnecting [!webSocketOpenedGuard && !webSocketStoppedGuard] = sWebSocketClose,
                sWebSocketClose + on_entry<_> / (webSocketConnect),
                sWebSocketClose + event<WebSocketOpenEvent> = sWebSocketOpen,
                sWebSocketOpen + event<Hello> / (onHello, heartbeatStart, tryResume) = sHandshake,
                sHandshake + event<ResumedEvent> = X,
                sHandshake + event<InvalidSessionEvent> / tryAuthLater = sAuth,
                sAuth + event<Ready> / (onReady) = X,
                X + on_entry<_> [webSocketOpenedGuard] / (reconnectAttemptReset, process(ReconnectingDone{})),
                // count attempts?
                state<_> + unexpected_event<WebSocketCloseEvent> / []{LOG_F(ERROR, "Unexpected close!");} = sReconnecting,
                state<_> + unexpected_event<ReconnectEvent> / []{LOG_F(ERROR, "Attempt to reconnect again");} = sReconnecting
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
                *sDisconnecting + on_entry<_> / (heartbeatStop, webSocketDisconnect),
                sDisconnecting + event<WebSocketCloseEvent> / (webSocketStop) = sWebSocketClose,
                sDisconnecting [!webSocketOpenedGuard && webSocketStoppedGuard] = X,
                sDisconnecting [!webSocketOpenedGuard && !webSocketStoppedGuard] / (webSocketStop) = sWebSocketClose,
                sWebSocketClose + event<WebSocketStopEvent> = X,
                sWebSocketClose [webSocketStoppedGuard] = X,
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
                state<StateCompositeConnecting> + event<ConnectingFailed> = state<StateCompositeDisconnecting>,
                sConnected + event<ReconnectEvent> = state<StateCompositeReconnecting>,
                sConnected + event<WebSocketCloseEvent> = state<StateCompositeReconnecting>,
                sConnected + event<LostHeartbeatEvent> = state<StateCompositeReconnecting>,
                state<StateCompositeReconnecting> + event<ReconnectingDone> = sConnected,
                state<StateCompositeReconnecting> + event<ReconnectingFailed> = state<StateCompositeDisconnecting>,
                sConnected + event<RequestDisconnectEvent> = state<StateCompositeDisconnecting>,
                state<StateCompositeDisconnecting> + event<DisconnectingDone> = sDisconnected,
                sDisconnected + on_entry<_> / doStop
            );
        }
    };

    class StateMachine
    {
        struct my_logger {
            template <class SM, class TEvent>
            void log_process_event(const TEvent&)
            {
                LOG_F(INFO, "[{}][process_event] {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TEvent>()
                );
            }

            template <class SM, class TGuard, class TEvent>
            void log_guard(const TGuard&, const TEvent&, bool result)
            {
                LOG_F(INFO, "[{}][guard] {} {} {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TGuard>(),
                    boost::sml::aux::get_type_name<TEvent>(),
                    (result ? "[OK]" : "[Reject]")
                );
            }

            template <class SM, class TAction, class TEvent>
            void log_action(const TAction&, const TEvent&)
            {
                LOG_F(INFO, "[{}][action] {} {}",
                    boost::sml::aux::get_type_name<SM>(),
                    boost::sml::aux::get_type_name<TAction>(),
                    boost::sml::aux::get_type_name<TEvent>()
                );
            }

            template <class SM, class TSrcState, class TDstState>
            void log_state_change(const TSrcState& src, const TDstState& dst)
            {
                LOG_F(INFO, "[{}][transition] {} -> {}",
                    boost::sml::aux::get_type_name<SM>(),
                    src.c_str(),
                    dst.c_str()
                );
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
        case StateMachineEventType::RequestReconnect:
            machine->machine.process_event(ReconnectEvent{});
            break;
        case StateMachineEventType::WebSocketOpen:
            machine->machine.process_event(WebSocketOpenEvent{});
            break;
        case StateMachineEventType::WebSocketClose:
            machine->machine.process_event(WebSocketCloseEvent{});
            break;
        case StateMachineEventType::WebSocketStop:
            machine->machine.process_event(WebSocketStopEvent{});
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
        case GatewayOpCode::InvalidSession:
        {
            machine->machine.process_event(InvalidSessionEvent{});
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
