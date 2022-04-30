#pragma once

#include <libadb/api/gateway/data/opcode.hpp>

#define HFSM2_ENABLE_PLANS
#include <hfsm2/machine.hpp>

namespace adb::api
{
    class GatewayController;

    using Config = hfsm2::Config::ContextT<GatewayController*>;
    using Machine = hfsm2::MachineT<Config>;

    using FSM = Machine::PeerRoot<
        struct Disconnected,
        struct Connected,
        Machine::Composite<
            struct Connecting,
            struct WebSocketOpen,
            struct Handshake,
            struct HearbeatStart,
            struct Auth
        >
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