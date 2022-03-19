#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/channel.hpp>
#include <libadb/api/guild/data/create-guild-channel-params.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;

    class GuildApi
    {
        friend DiscordApi;
    public:
        LIBADB_API std::vector<Channel> getChannels(adb::types::SFID guildId) const;
        /**
         * @brief Create a Channel in the Guild
         * @details https://discord.com/developers/docs/resources/guild#create-guild-channel
         * @param guildId Guild ID
         * @param params Parameters of the channel
         * @param reason Reason, that will be displayed in audit log
         * @return Channel, of succeed 
         */
        LIBADB_API std::optional<Channel> createChannel(adb::types::SFID guildId,
            const CreateGuildChannelParams &params, std::optional<std::string> reason = {});
    private:
        GuildApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}