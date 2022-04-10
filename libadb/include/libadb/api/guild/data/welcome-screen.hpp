#pragma once

#include <vector>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/guild/data/welcome-screen-channel.hpp>

namespace adb::api
{
    /**
     * @brief Welcome Screen
     * @details https://discord.com/developers/docs/resources/guild#welcome-screen-object
     */
    struct WelcomeScreen
    {
        /// the server description shown in the welcome screen
        adb::types::Nullable<std::string> description;
        /// the channels shown in the welcome screen, up to 5
        std::vector<WelcomeScreenChannel> welcomeChannels;
    };

    LIBADB_API void to_json(nlohmann::json& j, const WelcomeScreen& welcomeScreen);
    LIBADB_API void from_json(const nlohmann::json& j, WelcomeScreen& welcomeScreen);
}