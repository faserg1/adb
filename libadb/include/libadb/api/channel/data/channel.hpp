#pragma once

#include <string>
#include <optional>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/time.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/channel/data/channel-type.hpp>
#include <libadb/api/channel/data/overwrite.hpp>
#include <libadb/api/channel/data/video-quality-mode.hpp>
#include <libadb/api/channel/data/thread-metadata.hpp>
#include <libadb/api/channel/data/thread-member.hpp>
#include <libadb/api/permissions/permissions.hpp>
namespace adb::api
{
    /**
     * @brief Channel Object
     * @details https://discord.com/developers/docs/resources/channel#channel-object
     */
    struct Channel
    {
        /// the id of this channel
        adb::types::SFID id;
        /// the type of channel
        ChannelType type;
        /// the id of the guild (may be missing for some channel objects received over gateway guild dispatches)
        std::optional<adb::types::SFID> guildId;
        /// sorting position of the channel
        std::optional<int> position;
        /// explicit permission overwrites for members and roles
        std::optional<std::vector<Overwrite>> permissionOverwrites;
        /// the name of the channel (1-100 characters)
        std::optional<std::string> name;
        /// the channel topic (0-1024 characters)
        std::optional<adb::types::Nullable<std::string>> topic;
        /// whether the channel is nsfw
        std::optional<bool> nsfw;
        /// the id of the last message sent in this channel (may not point to an existing or valid message)
        std::optional<adb::types::Nullable<adb::types::SFID>> lastMessageId;
        /// the bitrate (in bits) of the voice channel
        std::optional<int> bitrate;
        /// the user limit of the voice channel
        std::optional<int> userLimit;
        /// amount of seconds a user has to wait before sending another message (0-21600);
        /// bots, as well as users with the permission manage_messages or manage_channel, are unaffected
        std::optional<int> rateLimitPerUser;
        /// the recipients of the DM
        std::optional<std::vector<User>> recipients;
        /// icon hash of the group DM
        std::optional<adb::types::Nullable<adb::resource::Image>> icon;
        /// id of the creator of the group DM or thread
        std::optional<adb::types::SFID> ownerId;
        /// application id of the group DM creator if it is bot-created
        std::optional<adb::types::SFID> applicationId;
        /// for guild channels: id of the parent category for a channel
        /// (each parent category can contain up to 50 channels),
        // for threads: id of the text channel this thread was created
        std::optional<adb::types::Nullable<adb::types::SFID>> parentId;
        /// when the last pinned message was pinned.
        /// This may be null in events such as GUILD_CREATE when a message is not pinned.
        std::optional<adb::types::Nullable<adb::types::TimePoint>> lastPinTimestamp;
        /// voice region id for the voice channel, automatic when set to null
        std::optional<adb::types::Nullable<std::string>> rtcRegion;
        /// the camera video quality mode of the voice channel, 1 when not present
        std::optional<VideoQualityMode> videoQualityMode;
        /// an approximate count of messages in a thread, stops counting at 50
        std::optional<size_t> messageCount;
        /// an approximate count of users in a thread, stops counting at 50
        std::optional<size_t> memberCount;
        /// thread-specific fields not needed by other channels
        std::optional<ThreadMetadata> threadMetadata;
        /// thread member object for the current user, if they have joined the thread, only included on certain API endpoints
        std::optional<ThreadMember> threadMember;
        /// default duration that the clients (not the API) will use for newly created threads, in minutes,
        /// to automatically archive the thread after recent activity, can be set to: 60, 1440, 4320, 10080
        std::optional<size_t> defailtAutoArchiveDuration;
        /// computed permissions for the invoking user in the channel, including overwrites
        /// only included when part of the `resolved` data received on a slash command interaction
        std::optional<Permissions> permissions;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Channel& channel);
    LIBADB_API void from_json(const nlohmann::json& j, Channel& channel);
}