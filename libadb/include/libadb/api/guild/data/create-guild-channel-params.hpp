#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>
#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/channel/data/channel-type.hpp>
#include <libadb/api/channel/data/overwrite.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Create Guild Channel Params
     * @details https://discord.com/developers/docs/resources/guild#create-guild-channel
     */
    struct CreateGuildChannelParams
    {
        /// channel name (1-100 characters)
        std::string name;
        /// the type of channel
        std::optional<ChannelType> type;
        /// channel topic (0-1024 characters)
        std::optional<std::string> topic;
        /// the bitrate (in bits) of the voice channel (voice only)
        std::optional<uint64_t> bitrate;
        /// the user limit of the voice channel (voice only)
        std::optional<uint64_t> userLimit;
        /// amount of seconds a user has to wait before sending another message (0-21600);
        /// bots, as well as users with the permission manage_messages or manage_channel, are unaffected
        std::optional<uint64_t> rateLimitPerUser;
        /// sorting position of the channel
        std::optional<uint64_t> position;
        /// the channel's permission overwrites
        std::optional<std::vector<Overwrite>> permissionOverwrites;
        /// id of the parent category for a channel
        std::optional<adb::types::SFID> parentId;
        /// whether the channel is nsfw
        std::optional<bool> nsfw;
    };
    
    LIBADB_API void to_json(nlohmann::json& j, const CreateGuildChannelParams& params);
    LIBADB_API void from_json(const nlohmann::json& j, CreateGuildChannelParams& params);
}