#pragma once

#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Followed Channel
     * @details https://discord.com/developers/docs/resources/channel#followed-channel-object
     */
    struct FollowedChannel
    {
        /// source channel id
        adb::types::SFID channelId;
        /// created target webhook id
        adb::types::SFID webhookId;
    };

    LIBADB_API void to_json(nlohmann::json& j, const FollowedChannel& channel);
    LIBADB_API void from_json(const nlohmann::json& j, FollowedChannel& channel);
}