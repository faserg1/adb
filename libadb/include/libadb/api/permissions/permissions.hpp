#pragma once

#include <cstdint>
#include <string>
#include <libadb/libadb.hpp>
#include <libadb/types/helpers/enums.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /** @brief Permissions for Auth
     * @details https://discord.com/developers/docs/topics/permissions
     */
    enum class Permission : uint64_t
    {
        CREATE_INSTANT_INVITE = 	 ((uint64_t)1 << 0), ///< Allows creation of instant invites
        KICK_MEMBERS = 				 ((uint64_t)1 << 1), ///< Allows kicking members	
        BAN_MEMBERS = 				 ((uint64_t)1 << 2), ///< Allows banning members	
        ADMINISTRATOR = 			 ((uint64_t)1 << 3), ///< Allows all permissions and bypasses channel permission overwrites	
        MANAGE_CHANNELS = 			 ((uint64_t)1 << 4), ///< Allows management and editing of channels
        MANAGE_GUILD = 				 ((uint64_t)1 << 5), ///< Allows management and editing of the guild
        ADD_REACTIONS = 			 ((uint64_t)1 << 6), ///< Allows for the addition of reactions to messages
        VIEW_AUDIT_LOG = 			 ((uint64_t)1 << 7), ///< Allows for viewing of audit logs
        PRIORITY_SPEAKER = 			 ((uint64_t)1 << 8), ///< Allows for using priority speaker in a voice channel
        STREAM = 					 ((uint64_t)1 << 9),  ///< Allows the user to go live
        VIEW_CHANNEL = 				 ((uint64_t)1 << 10), ///< Allows guild members to view a channel, which includes reading messages in text channels
        SEND_MESSAGES = 			 ((uint64_t)1 << 11), ///< Allows for sending messages in a channel (does not allow sending messages in threads)
        SEND_TTS_MESSAGES = 		 ((uint64_t)1 << 12), ///< Allows for sending of /tts messages
        MANAGE_MESSAGES = 			 ((uint64_t)1 << 13), ///< Allows for deletion of other users messages
        EMBED_LINKS = 				 ((uint64_t)1 << 14), ///< Links sent by users with this permission will be auto-embedded
        ATTACH_FILES = 				 ((uint64_t)1 << 15), ///< Allows for uploading images and files
        READ_MESSAGE_HISTORY = 		 (uint64_t)(1 << 16), ///< Allows for reading of message history
        MENTION_EVERYONE = 			 ((uint64_t)1 << 17), ///< Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel
        USE_EXTERNAL_EMOJIS = 		 ((uint64_t)1 << 18), ///< Allows the usage of custom emojis from other servers
        VIEW_GUILD_INSIGHTS = 		 ((uint64_t)1 << 19), ///< Allows for viewing guild insights	
        CONNECT = 					 ((uint64_t)1 << 20), ///< Allows for joining of a voice channel
        SPEAK = 					 ((uint64_t)1 << 21), ///< Allows for speaking in a voice channel
        MUTE_MEMBERS = 				 ((uint64_t)1 << 22), ///< Allows for muting members in a voice channel
        DEAFEN_MEMBERS = 			 ((uint64_t)1 << 23), ///< Allows for deafening of members in a voice channel
        MOVE_MEMBERS = 				 ((uint64_t)1 << 24), ///< Allows for moving of members between voice channels
        USE_VAD = 					 ((uint64_t)1 << 25), ///< Allows for using voice-activity-detection in a voice channel
        CHANGE_NICKNAME = 			 ((uint64_t)1 << 26), ///< Allows for modification of own nickname	
        MANAGE_NICKNAMES = 			 ((uint64_t)1 << 27), ///< Allows for modification of other users nicknames	
        MANAGE_ROLES = 				 ((uint64_t)1 << 28), ///< Allows management and editing of roles
        MANAGE_WEBHOOKS = 			 ((uint64_t)1 << 29), ///< Allows management and editing of webhooks
        MANAGE_EMOJIS_AND_STICKERS = ((uint64_t)1 << 30), ///< Allows management and editing of emojis and stickers	
        USE_APPLICATION_COMMANDS = 	 ((uint64_t)1 << 31), ///< Allows members to use application commands, including slash commands and context menu commands.
        REQUEST_TO_SPEAK = 			 ((uint64_t)1 << 32), ///< Allows for requesting to speak in stage channels. (This permission is under active development and may be changed or removed.)
        MANAGE_EVENTS = 			 ((uint64_t)1 << 33), ///< Allows for creating, editing, and deleting scheduled events
        MANAGE_THREADS = 			 ((uint64_t)1 << 34), ///< Allows for deleting and archiving threads, and viewing all private threads
        CREATE_PUBLIC_THREADS = 	 ((uint64_t)1 << 35), ///< Allows for creating threads
        CREATE_PRIVATE_THREADS = 	 ((uint64_t)1 << 36), ///< Allows for creating private threads
        USE_EXTERNAL_STICKERS = 	 ((uint64_t)1 << 37), ///< Allows the usage of custom stickers from other servers
        SEND_MESSAGES_IN_THREADS = 	 ((uint64_t)1 << 38), ///< Allows for sending messages in threads
        START_EMBEDDED_ACTIVITIES =  ((uint64_t)1 << 39)  ///< Allows for launching activities (applications with the EMBEDDED flag) in a voice channel
    };

    ADB_ENUM_FLAGS_OPERATORS(Permission, Permissions, uint64_t)

    LIBADB_API void from_string(const std::string &str, Permissions &permissions);
    LIBADB_API std::string to_string(Permissions permissions);
}