#pragma once

#include <cstdint>

namespace adb::api
{
    /** @brief Gateway Opcodes
     * @details https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes
     */
    enum class GatewayOpCode : uint8_t
    {
        /// An event was dispatched.
        /// Receive
        Dispatch = 0,
        /// Fired periodically by the client to keep the connection alive.
        /// Send/Receive
        Heartbeat = 1,
        /// Starts a new session during the initial handshake.
        /// Send
        Identify = 2,
        /// Update the client's presence.
        /// Send
        PresenceUpdate = 3,
        /// Used to join/leave or move between voice channels.
        /// Send
        VoiceStateUpdate = 4,
        /// Resume a previous session that was disconnected.
        /// Send
        Resume = 6,
        /// You should attempt to reconnect and resume immediately.
        /// Receive
        Reconnect = 7,
        /// Request information about offline guild members in a large guild.
        /// Send
        RequestGuildMembers = 8,
        /// The session has been invalidated. You should reconnect and identify/resume accordingly.
        /// Receive
        InvalidSession = 9,
        /// Sent immediately after connecting, contains the heartbeat_interval to use.
        /// Receive
        Hello = 10,
        /// Sent in response to receiving a heartbeat to acknowledge that it has been received.
        /// Receive
        HeartbeatACK = 11
    };
}