#pragma once

#include <cstdint>

namespace adb::api
{
    /** @brief Voice Opcodes
     * @details https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice
     */
    enum class VoiceOpCode : uint8_t
    {
        /// Begin a voice websocket connection.
        /// Send
        Identify = 0,
        /// Select the voice protocol.
        /// Send
        SelectProtocol = 1,
        /// Complete the websocket handshake.
        /// Receive
        Ready = 2,
        /// Keep the websocket connection alive.
        /// Send
        Heartbeat = 3, 
        /// Describe the session.
        /// Receive
        SessionDescription = 4,
        /// Indicate which users are speaking.
        /// Send/Receive
        Speaking = 5,
        /// Sent to acknowledge a received client heartbeat.
        /// Receive
        HeartbeatACK = 6,
        /// Resume a connection.
        /// Send
        Resume = 7,
        /// Time to wait between sending heartbeats in milliseconds.
        /// Receive
        Hello = 8,
        /// Acknowledge a successful session resume.
        /// Receive
        Resumed = 9,
        /// A client has disconnected from the voice channel
        /// Receive
        ClientDisconnect = 13
    };
}