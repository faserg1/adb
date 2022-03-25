#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/channel.hpp>
#include <libadb/api/permissions/role.hpp>
#include <libadb/api/guild/data/create-guild-channel-params.hpp>
#include <libadb/api/guild/data/create-guild-role-params.hpp>
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
         * @return Channel, if succeed 
         */
        LIBADB_API std::optional<Channel> createChannel(adb::types::SFID guildId,
            const CreateGuildChannelParams &params, std::optional<std::string> reason = {});
        /**
         * @brief Create a Role in the Guild
         * @details https://discord.com/developers/docs/resources/guild#create-guild-role
         * @param guildId Guild ID
         * @param params Parameters of the role
         * @param reason  Reason, that will be displayed in audit log
         * @return Role, if succeed 
         */
        LIBADB_API std::optional<Role> createRole(const adb::types::SFID &guildId,
            const CreateGuildRoleParams &params, std::optional<std::string> reason = {});

        LIBADB_API bool addMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
            std::optional<std::string> reason = {});
        LIBADB_API bool removeMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
            std::optional<std::string> reason = {});
    private:
        GuildApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}