#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/channel/data/channel-type.hpp>
#include <libadb/api/channel/data/overwrite.hpp>
#include <libadb/libadb.hpp>

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
        

    };

    LIBADB_API void to_json(nlohmann::json& j, const Channel& channel);
    LIBADB_API void from_json(const nlohmann::json& j, Channel& channel);
}