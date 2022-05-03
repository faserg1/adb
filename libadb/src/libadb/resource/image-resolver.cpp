#include <libadb/resource/image-resolver.hpp>
#include <fmt/format.h>
using namespace adb::resource;
using namespace adb::types;

Image ImageResolver::getCustomEmoji(const adb::types::SFID &id)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF}, "emojis/", id.to_string());
}

Image ImageResolver::getGroupDMIcon(const std::string &hash)
{
    return Image({ImageFormat::PNG}, "assets/", hash);
}

Image ImageResolver::getGuildIcon(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        fmt::format("icons/{}/", guildId.to_string()), hash, true);
}

Image ImageResolver::getGuildSplash(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("splashes/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getGuildDiscoverySplash(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("discovery-splashes/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getGuildBanner(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("banners/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getUserBanner(const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        fmt::format("banners/{}/", userId.to_string()), hash, true);
}

Image ImageResolver::getDefaultUserAvatar(const std::string &discriminator)
{
    auto modulo = std::atoi(discriminator.data()) % 5;
    return Image({ImageFormat::PNG}, "embed/avatars/", std::to_string(modulo));
}

Image ImageResolver::getUserAvarar(const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        fmt::format("avatars/{}/", userId.to_string()), hash, true);
}

Image ImageResolver::getGuildMemberAvatar(const adb::types::SFID &guildId, const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        fmt::format("guilds/{}/users/{}/avatars/", guildId.to_string(), userId.to_string()), hash, true);
}

Image ImageResolver::getApplicationIcon(const adb::types::SFID &appId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("team-icons/{}/", appId.to_string()), hash, true);
}

Image ImageResolver::getApplicationCover(const adb::types::SFID &appId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("app-icons/{}/", appId.to_string()), hash, true);
}

Image ImageResolver::getTeamIcon(const adb::types::SFID &teamId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("app-icons/{}/", teamId.to_string()), hash, true);
}

Image ImageResolver::getRoleIcon(const adb::types::SFID &roleId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("role-icons/{}/", roleId.to_string()), hash, true);
}

Image ImageResolver::getGuildScheduledEventCover(const adb::types::SFID &eventId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        fmt::format("guild-events/{}/", eventId.to_string()), hash, false);
}