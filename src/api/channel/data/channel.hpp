#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <types/snowflake.hpp>
#include <api/user/data/user.hpp>
#include "channel-type.hpp"
#include "overwrite.hpp"
namespace adb::api
{
    /**
     * @brief Channel Object
     * @details https://discord.com/developers/docs/resources/channel#channel-object
     */
    struct Channel
    {
        /// 
        adb::types::SFID id;
        /// 
        ChannelType type;
        /// 
        std::optional<adb::types::SFID> guildId;
        /// 
        std::optional<int> position;
        /// 
        std::optional<std::vector<Overwrite>> permissionOverwrites;
        /// 
        std::optional<std::string> name;
        /// 
        std::optional<std::string> topic;
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
        std::optional<std::string> iconHash;
        

    };
}