#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/channel.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;

    class GuildApi
    {
        friend DiscordApi;
    public:
        LIBADB_API std::vector<Channel> getChannels(adb::types::SFID guildId) const;
    private:
        GuildApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}