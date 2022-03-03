#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/channel.hpp>

namespace adb::api
{
    class DiscordApi;

    class GuildApi
    {
        friend DiscordApi;
    public:
        std::vector<Channel> getChannels(adb::types::SFID guildId) const;
    private:
        GuildApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}