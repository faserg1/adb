#pragma once

#include <libadb/api/gateway/data/opcode.hpp>
#include <memory>
namespace adb::api
{
    class GatewayController;
    struct Payload;

    enum class StateMachineEventType
    {
        RequestConnect,
        RequestDisconnect,
        WebSocketOpen,
        WebSocketClose,
        WebSocketStop,
        WebSocketFail,
        LostHeartbeat,
        HeartbeatStart,
        HeartbeatStop,
        Payload
    };

    class StateMachine;

    std::shared_ptr<StateMachine> createStateMachine(GatewayController *controller);
    void processEvent(std::shared_ptr<StateMachine> machine, StateMachineEventType event, const Payload *payload = nullptr);
}