#pragma once

#include <string>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>

namespace adb::api
{
    /**
     * @brief Welcome Screen Channel
     * @details https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure
     */
    struct WelcomeScreenChannel
    {
        /// the channel's id
        adb::types::SFID channelId;
        /// the description shown for the channel
        std::string description;
        /// the emoji id, if the emoji is custom
        adb::types::Nullable<adb::types::SFID> emojiId;
        /// the emoji name if custom, the unicode character if standard, or null if no emoji is set
        adb::types::Nullable<std::string> emojiName;
    };

    LIBADB_API void to_json(nlohmann::json& j, const WelcomeScreenChannel& channel);
    LIBADB_API void from_json(const nlohmann::json& j, WelcomeScreenChannel& channel);
}