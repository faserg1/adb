#pragma once

#include <libadb/api/gateway/data/opcode.hpp>

#define HFSM2_ENABLE_PLANS
#include <hfsm2/machine.hpp>

namespace adb::api
{
    class GatewayController;

    using Config = hfsm2::Config::ContextT<GatewayController*>;
    using Machine = hfsm2::MachineT<Config>;

    /* Main states */

    struct Disconnected;
    struct Connected;

    /* Inner Head States */

    struct Connecting;
    struct Reconnecting;

    /* Inner States */

    struct WebSocketOpen;
    struct WebSocketStop;
    struct HeartbeatStart;
    struct HeartbeatStop;
    struct Handshake;
    struct Auth;
    struct Resuming;

    using FSM = Machine::PeerRoot<
        /* Main states */
        Disconnected,
        Connected,

        /* Head transition states */
        Connecting,
        Reconnecting,

        /* Transition states */

        WebSocketOpen,
        WebSocketStop,

        HeartbeatStart,
        HeartbeatStop,

        Handshake,
        Auth,
        Resuming
        
        /*Machine::Composite<
            struct Disconnecting,
            struct HeartbeatStop
        >,*/
        /*Machine::Composite<
            struct Resuming,
            struct Connecting,
            struct Resuming
        >*/
    >;

    enum class FSMEventType
    {
        Payload,

        ThreadHeartbeatStop,
        ThreadWebsocketStop,

        GatewayUserRequest_None,
        GatewayUserRequest_Connect,
        GatewayUserRequest_Disconnect,

        GatewayRequest_Reconnect,

        WebSocketEventType_Open,
        WebSocketEventType_Fail,
        WebSocketEventType_Close,
        WebSocketEventType_LostHeartbeat
    };

    struct FSMEvent
    {
        FSMEventType type;
        const Payload *payload = nullptr;
    };
}