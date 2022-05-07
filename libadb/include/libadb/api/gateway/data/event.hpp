#pragma once

#include <string>
#include <cstdint>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Gateway Event
     * @details https://discord.com/developers/docs/topics/gateway#commands-and-events-gateway-events
     */
    enum class Event : uint64_t
    {
        UNKNOWN,
        /// defines the heartbeat interval
        HELLO,
        /// contains the initial state information
        READY,
        /// response to Resume
        RESUMED,
        /// server is going away, client should reconnect to gateway and resume
        RECONNECT,
        /// failure response to Identify or Resume or invalid active session
        INVALID_SESSION,
        /// application command permission was updated
        APPLICATION_COMMAND_PERMISSIONS_UPDATE,
        /// new guild channel created
        CHANNEL_CREATE,
        /// channel was updated
        CHANNEL_UPDATE,
        /// channel was deleted
        CHANNEL_DELETE,
        /// message was pinned or unpinned
        CHANNEL_PINS_UPDATE,
        /// thread created, also sent when being added to a private thread
        THREAD_CREATE,
        /// thread was updated
        THREAD_UPDATE,
        /// thread was deleted
        THREAD_DELETE,
        /// sent when gaining access to a channel, contains all active threads in that channel
        THREAD_LIST_SYNC,
        /// thread member for the current user was updated
        THREAD_MEMBER_UPDATE,
        /// some user(s) were added to or removed from a thread
        THREAD_MEMBERS_UPDATE,
        /// lazy-load for unavailable guild, guild became available, or user joined a new guild
        GUILD_CREATE,
        /// guild was updated
        GUILD_UPDATE,
        /// guild became unavailable, or user left/was removed from a guild
        GUILD_DELETE,
        /// user was banned from a guild
        GUILD_BAN_ADD,
        /// user was unbanned from a guild
        GUILD_BAN_REMOVE,
        /// guild emojis were updated
        GUILD_EMOJIS_UPDATE,
        /// guild stickers were updated
        GUILD_STICKERS_UPDATE,
        /// guild integration was updated
        GUILD_INTEGRATIONS_UPDATE,
        /// new user joined a guild
        GUILD_MEMBER_ADD,
        /// user was removed from a guild
        GUILD_MEMBER_REMOVE,
        /// guild member was updated
        GUILD_MEMBER_UPDATE,
        /// response to Request Guild Members
        GUILD_MEMBERS_CHUNK,
        /// guild role was created
        GUILD_ROLE_CREATE,
        /// guild role was updated
        GUILD_ROLE_UPDATE,
        /// guild role was deleted
        GUILD_ROLE_DELETE,
        /// guild scheduled event was created
        GUILD_SCHEDULED_EVENT_CREATE,
        /// guild scheduled event was updated
        GUILD_SCHEDULED_EVENT_UPDATE,
        /// guild scheduled event was deleted
        GUILD_SCHEDULED_EVENT_DELETE,
        /// user subscribed to a guild scheduled event
        GUILD_SCHEDULED_EVENT_USER_ADD,
        /// user unsubscribed from a guild scheduled event
        GUILD_SCHEDULED_EVENT_USER_REMOVE,
        /// guild integration was created
        INTEGRATION_CREATE,
        /// guild integration was updated
        INTEGRATION_UPDATE,
        /// guild integration was deleted
        INTEGRATION_DELETE,
        /// user used an interaction, such as an Application Command
        INTERACTION_CREATE,
        /// invite to a channel was created
        INVITE_CREATE,
        /// invite to a channel was deleted
        INVITE_DELETE,
        /// message was created
        MESSAGE_CREATE,
        /// message was edited
        MESSAGE_UPDATE,
        /// message was deleted
        MESSAGE_DELETE,
        /// multiple messages were deleted at once
        MESSAGE_DELETE_BULK,
        /// user reacted to a message
        MESSAGE_REACTION_ADD,
        /// user removed a reaction from a message
        MESSAGE_REACTION_REMOVE,
        /// all reactions were explicitly removed from a message
        MESSAGE_REACTION_REMOVE_ALL,
        /// all reactions for a given emoji were explicitly removed from a message
        MESSAGE_REACTION_REMOVE_EMOJI,
        /// user was updated
        PRESENCE_UPDATE,
        /// stage instance was created
        STAGE_INSTANCE_CREATE,
        /// stage instance was deleted or closed
        STAGE_INSTANCE_DELETE,
        /// stage instance was updated
        STAGE_INSTANCE_UPDATE,
        /// user started typing in a channel
        TYPING_START,
        /// properties about the user changed
        USER_UPDATE,
        /// someone joined, left, or moved a voice channel
        VOICE_STATE_UPDATE,
        /// guild's voice server was updated
        VOICE_SERVER_UPDATE,
        /// guild channel webhook was created, update, or deleted
        WEBHOOKS_UPDATE,
    };

    LIBADB_API std::string to_string(Event e);
    LIBADB_API Event from_string(std::string_view str);
}