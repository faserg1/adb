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
        std::format("icons/{}/", guildId.to_string()), hash, true);
}

Image ImageResolver::getGuildSplash(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        std::format("splashes/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getGuildDiscoverySplash(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        std::format("discovery-splashes/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getGuildBanner(const adb::types::SFID &guildId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP},
        std::format("banners/{}/", guildId.to_string()), hash);
}

Image ImageResolver::getUserBanner(const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        std::format("banners/{}/", userId.to_string()), hash, true);
}

Image ImageResolver::getDefaultUserAvatar(const std::string &discriminator)
{
    auto modulo = std::atoi(discriminator.data()) % 5;
    return Image({ImageFormat::PNG}, "embed/avatars/", std::to_string(modulo));
}

Image ImageResolver::getUserAvarar(const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        std::format("avatars/{}/", userId.to_string()), hash, true);
}

Image ImageResolver::getGuildMemberAvatar(const adb::types::SFID &guildId, const adb::types::SFID &userId, const std::string &hash)
{
    return Image({ImageFormat::PNG, ImageFormat::JPEG, ImageFormat::WebP, ImageFormat::GIF},
        std::format("guilds/{}/users/{}/avatars/", guildId.to_string(), userId.to_string()), hash, true);
}