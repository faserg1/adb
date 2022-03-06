#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
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
        /// 
        std::optional<adb::types::Nullable<std::string>> topic;
        /// 
        std::optional<bool> nsfw;
        /// 
        std::optional<adb::types::SFID> lastMessageId;
        /// 
        std::optional<int> bitrate;
        /// 
        std::optional<int> userLimit;
        /// 
        std::optional<int> rateLimitPerUser;
        /// 
        std::optional<std::vector<User>> recipients;
        ///
        std::optional<adb::types::Nullable<std::string>> iconHash;
        

    };

    LIBADB_API void to_json(nlohmann::json& j, const Channel& channel);
    LIBADB_API void from_json(const nlohmann::json& j, Channel& channel);
}