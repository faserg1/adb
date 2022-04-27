#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/channel.hpp>
#include <libadb/api/permissions/role.hpp>
#include <libadb/api/guild/data/guild.hpp>
#include <libadb/api/guild/data/create-guild-channel-params.hpp>
#include <libadb/api/guild/data/create-guild-role-params.hpp>
#include <libadb/api/guild/data/guild-member.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;
    class Context;

    class GuildApi
    {
        friend DiscordApi;
    public:
        /**
         * @brief Returns the guild object for the given id.
         * @details https://discord.com/developers/docs/resources/guild#get-guild
         * @param guildId Guild ID
         * @param withCounst when true, will return approximate member and presence counts for the guild
         */
        LIBADB_API std::optional<Guild> getGuild(const adb::types::SFID &guildId, bool withCounst = false) const;
        LIBADB_API std::vector<Channel> getChannels(const adb::types::SFID &guildId) const;
        /**
         * @brief Create a Channel in the Guild
         * @details https://discord.com/developers/docs/resources/guild#create-guild-channel
         * @param guildId Guild ID
         * @param params Parameters of the channel
         * @param reason Reason, that will be displayed in audit log
         * @return Channel, if succeed 
         */
        LIBADB_API std::optional<Channel> createChannel(const adb::types::SFID &guildId,
            const CreateGuildChannelParams &params, std::optional<std::string> reason = {});
        /**
         * @brief Get Guild Member for specefic user
         * @details https://discord.com/developers/docs/resources/guild#get-guild-member
         * @param guildId Guild ID
         * @param userId User ID
         */
        LIBADB_API std::optional<GuildMember> getGuildMember(const adb::types::SFID &guildId, const adb::types::SFID &userId);
        /**
         * @brief Get the list of Guild Members that are members of the guild.
         * @details https://discord.com/developers/docs/resources/guild#list-guild-members
         * @param guildId Guild ID
         * @param limit max number of members to return (1-1000)
         * @param after the highest user id in the previous page
         */
        LIBADB_API std::vector<GuildMember> listGuildMembers(const adb::types::SFID &guildId,
            std::optional<uint64_t> limit, std::optional<adb::types::SFID> after);
        /**
         * @brief Search for guild members whose username or nickname starts with a provided string.
         * @details https://discord.com/developers/docs/resources/guild#search-guild-members
         * @param guildId Guild ID
         * @param query Query string to match username(s) and nickname(s) against.
         * @param limit max number of members to return (1-1000)
         */
        LIBADB_API std::vector<GuildMember> searchGuildMembers(const adb::types::SFID &guildId,
            std::string query, std::optional<uint64_t> limit);
        /**
         * @brief Get the Roles of the Guild
         * @details https://discord.com/developers/docs/resources/guild#get-guild-roles
         * @param guildId Guild ID
         * @return Guild roles, of succeed 
         */
        LIBADB_API std::vector<Role> getRoles(const adb::types::SFID &guildId);
        /**
         * @brief Create a Role in the Guild
         * @details https://discord.com/developers/docs/resources/guild#create-guild-role
         * @param guildId Guild ID
         * @param params Parameters of the role
         * @param reason Reason, that will be displayed in audit log
         * @return Role, if succeed 
         */
        LIBADB_API std::optional<Role> createRole(const adb::types::SFID &guildId,
            const CreateGuildRoleParams &params, std::optional<std::string> reason = {});
        /**
         * @brief 
         * @details https://discord.com/developers/docs/resources/guild#delete-guild-role
         * @param guildId Guild ID
         * @param roleId Role ID to delete
         * @param reason Reason, that will be displayed in audit log
         * @return LIBADB_API 
         */
        LIBADB_API bool deleteRole(const adb::types::SFID &guildId,
            const adb::types::SFID &roleId, std::optional<std::string> reason = {});
        /**
         * @brief Adds a role to a guild member.
         * @details https://discord.com/developers/docs/resources/guild#add-guild-member-role
         * @param guildId Guild ID
         * @param userId User ID, who needs this role
         * @param roleId Role ID to add
         * @param reason Reason, that will be displayed in audit log
         * @return `true`, if succeed 
         */
        LIBADB_API bool addMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
            std::optional<std::string> reason = {});
        LIBADB_API bool removeMemberRole(const adb::types::SFID &guildId, const adb::types::SFID &userId, const adb::types::SFID &roleId,
            std::optional<std::string> reason = {});
    private:
        GuildApi(std::shared_ptr<Context> context);
    private:
        const std::shared_ptr<Context> context_;
        const std::string baseUrl_;
    };
}