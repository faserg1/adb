#include <libadb/api/gateway/gateway-fsm.hpp>
#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/ready.hpp>
using namespace adb::api;

namespace adb::api
{
    struct Disconnected : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->onStop();
        } 

        void react(const FSMEvent &event, FullControl& control) noexcept
        {
            if (event.type == FSMEventType::GatewayUserRequest_Connect)
            {
                control.changeTo<Connecting>();
            }
        }
    };

    struct Connected : FSM::State
    {
        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type == FSMEventType::GatewayRequest_Reconnect)
            {
                // todo: reconnect
            }
        }
    };

    struct Connecting : FSM::State
    {
        void enter(PlanControl& control) noexcept
        {
            auto plan = control.plan();

            plan.change<WebSocketOpen, Handshake>();
            plan.change<Handshake, HeartbeatStart>();
            plan.change<HeartbeatStart, Auth>();
        }

        void planSucceeded(FullControl& control) noexcept
        {
            control.changeTo<Connected>();
        }

        void planFailed(FullControl& control) noexcept
        {
            // todo normal disconnecting
            control.changeTo<Disconnected>();
        }
    };

    struct WebSocketOpen : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            if (!control.context()->connect())
                control.fail();
            control.context()->startWebSocket();
        }

        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            switch (event.type)
            {
            case FSMEventType::WebSocketEventType_Open:
                control.succeed();
                break;
            case FSMEventType::WebSocketEventType_Fail:
                control.fail();
                break;
            default:
                break;
            }
        }
    };

    struct WebSocketStop : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->stopWebSocket();
        }

        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type == FSMEventType::ThreadWebsocketStop)
                control.succeed();
        }
    };

    struct Handshake : FSM::State
    {
        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type != FSMEventType::Payload || !event.payload)
                return;
            if (event.payload->op == GatewayOpCode::Hello)
            {
                auto hello = event.payload->data.get<Hello>();
                control.context()->setHeartbeatInterval(hello.heartbeatInterval);
                control.succeed();
            }
        }
    };

    struct HeartbeatStart : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->scheduleUpdate();
        }

        void update(FullControl& control) noexcept {
            control.context()->startHeartbeat();
            control.succeed();
        }
    };

    struct HeartbeatStop : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->stopHeartbeat();
        }

        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type == FSMEventType::ThreadHeartbeatStop)
                control.succeed();
        }
    };

    struct Auth : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->identity();
        }

        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type != FSMEventType::Payload || !event.payload)
                return;
            if (event.payload->op != GatewayOpCode::Dispatch)
                return;
            auto eventType = from_string(event.payload->eventName.value());
            if (eventType == Event::READY)
            {
                auto ready = event.payload->data.get<Ready>();
                control.context()->saveSessionInfo(ready);
                control.succeed();
            }
            else if (eventType == Event::INVALID_SESSION)
            {
                auto resumable = event.payload->data.get<bool>();
                if (!resumable)
                    control.fail();
                else
                    control.changeTo<Reconnecting>();
            }
        }
    };

    struct Resuming : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            control.context()->resume();
        }

        void react(const FSMEvent& event, FullControl& control) noexcept
        {
            if (event.type != FSMEventType::Payload || !event.payload)
                return;
            if (event.payload->op != GatewayOpCode::Dispatch)
                return;
            auto eventType = from_string(event.payload->eventName.value());
            if (eventType == Event::READY)
            {
                auto ready = event.payload->data.get<Ready>();
                control.context()->saveSessionInfo(ready);
                control.succeed();
            }
            else if (eventType == Event::INVALID_SESSION)
            {
                auto resumable = event.payload->data.get<bool>();
                if (!resumable)
                    control.fail();
                else
                    control.changeTo<Reconnecting>();
            }
        }
    };

    struct Reconnecting : FSM::State
    {
        void entryGuard(FullControl& control) noexcept
        {
            // todo: count attempts
        }

        void enter(PlanControl& control) noexcept
        {
            auto plan = control.plan();

            plan.change<HeartbeatStop, WebSocketStop>();
            plan.change<WebSocketStop, WebSocketOpen>();
            plan.change<WebSocketOpen, Handshake>();
            plan.change<Handshake, HeartbeatStart>();
            plan.change<HeartbeatStart, Resuming>();
        }

        void planSucceeded(FullControl& control) noexcept
        {
            control.changeTo<Connected>();
        }

        void planFailed(FullControl& control) noexcept
        {
            // todo normal disconnecting
            control.changeTo<Disconnected>();
        }
    };
}