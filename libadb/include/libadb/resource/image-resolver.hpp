#pragma once

#include <libadb/libadb.hpp>
#include <string>
#include <libadb/types/snowflake.hpp>
#include <libadb/resource/image.hpp>

namespace adb::resource
{
    /**
     * @brief Image resolver will create Image object by provided params
     * @details https://discord.com/developers/docs/reference#image-formatting-cdn-endpoints
     */
    class ImageResolver
    {
        ImageResolver() = delete;
        ~ImageResolver() = delete;
    public:
        LIBADB_API static Image getCustomEmoji(const adb::types::SFID &id);
        LIBADB_API static Image getGroupDMIcon(const std::string &hash);
        LIBADB_API static Image getGuildIcon(const adb::types::SFID &guildId, const std::string &hash);
        LIBADB_API static Image getGuildSplash(const adb::types::SFID &guildId, const std::string &hash);
        LIBADB_API static Image getGuildDiscoverySplash(const adb::types::SFID &guildId, const std::string &hash);
        LIBADB_API static Image getGuildBanner(const adb::types::SFID &guildId, const std::string &hash);
        LIBADB_API static Image getUserBanner(const adb::types::SFID &userId, const std::string &hash);
        LIBADB_API static Image getDefaultUserAvatar(const std::string &discriminator);
        LIBADB_API static Image getUserAvarar(const adb::types::SFID &userId, const std::string &hash);
        LIBADB_API static Image getGuildMemberAvatar(const adb::types::SFID &guildId, const adb::types::SFID &userId, const std::string &hash);
        LIBADB_API static Image getApplicationIcon(const adb::types::SFID &appId, const std::string &hash);
        LIBADB_API static Image getApplicationCover(const adb::types::SFID &appId, const std::string &hash);
        LIBADB_API static Image getTeamIcon(const adb::types::SFID &teamId, const std::string &hash);
        LIBADB_API static Image getRoleIcon(const adb::types::SFID &roleId, const std::string &hash);
        LIBADB_API static Image getGuildScheduledEventCover(const adb::types::SFID &eventId, const std::string &hash);
    };
}
