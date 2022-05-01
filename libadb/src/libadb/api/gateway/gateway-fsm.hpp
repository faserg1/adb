#pragma once

#include <libadb/api/gateway/data/opcode.hpp>

#define HFSM2_ENABLE_PLANS
#define HFSM2_ENABLE_LOG_INTERFACE
#define HFSM2_ENABLE_VERBOSE_DEBUG_LOG
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
    struct Disconnecting;

    /* Inner States */

    struct WebSocketOpen;
    struct WebSocketStop;
    struct HeartbeatStart;
    struct HeartbeatStop;
    struct Handshake;
    struct Auth;
    struct Resuming;

    using FSM = Machine::PeerRoot<
        Disconnected,
        Connected,

        Machine::Composite<
            Connecting,
            struct ConnectingWebSocketOpen,
            struct ConnectingHandshake,
            struct ConnectingHeartbeatStart,
            Auth
        >,
        
        Machine::Composite<
            Reconnecting,
            struct ReconnectingHeartbeatStop,
            struct ReconnectingWebSocketStop,
            struct ReconnectingWebSocketOpen,
            struct ReconnectingHandshake,
            struct ReconnectingHeartbeatStart,
            Resuming
        >,

        Machine::Composite<
            Disconnecting,
            struct DisconnectingHeartbeatStop,
            struct DisconnectingWebSocketStop
        >
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