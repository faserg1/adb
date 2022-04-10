#include <libadb/api/guild/data/guild.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/resource/image-resolver.hpp>
#include <algorithm>
using namespace adb::api;
using namespace adb::types;
using namespace adb::resource;


template <class To, class From, class Func> std::vector<To> transform_to(const std::vector<From> &vec, Func f)
{
    std::vector<To> result;
    result.reserve(vec.size());
    std::transform(vec.begin(), vec.end(), std::back_inserter(result), f);
    return result;
}

void adb::api::to_json(nlohmann::json& j, const Guild& guild)
{
    j = nlohmann::json {};
    j["id"] = guild.id;
    j["name"] = guild.name;
    map_to_json(j, "icon", guild.icon);
    map_to_json(j, "icon_hash", guild.iconHash);
    map_to_json(j, "splash", guild.splash);
    map_to_json(j, "discovery_splash", guild.discoverySplash);
    j["owner_id"] = guild.ownerId;
    map_to_json(j, "afk_channel_id", guild.afkChannelId);
    j["afk_timeout"] = guild.afkTimeout;
    map_to_json(j, "widget_enabled", guild.widgetEnabled);
    map_to_json(j, "widget_channel_id", guild.widgetChannelId);
    j["verification_level"] = guild.verificationLevel;
    j["default_message_notifications"] = guild.defaultMessageNotifications;
    j["explicit_content_filter"] = guild.explicitContentFilter;
    j["roles"] = guild.roles;
    j["emojis"] = guild.emojis;
    j["features"] = transform_to<std::string>(guild.features, [](auto &feature) -> std::string
    {
        return to_string(feature);
    });
    map_to_json(j, "application_id", guild.applicationId);
    map_to_json(j, "system_channel_id", guild.systemChannelId);
    j["system_channel_flags"] = guild.systemChannelFlags;
    map_to_json(j, "max_presences", guild.maxPresences);
    map_to_json(j, "max_members", guild.maxMembers);
    map_to_json(j, "vanity_url_code", guild.vanityUrlCode);
    map_to_json(j, "description", guild.description);
    map_to_json(j, "banner", guild.banner);
    j["premium_tier"] = guild.premiumTier;
    map_to_json(j, "premium_subscription_count", guild.premiumSubscriptionCount);
    j["preferred_locale"] = to_string(guild.preferredLocale);
    map_to_json(j, "public_update_channel_id", guild.publicUpdateChannelId);
    map_to_json(j, "max_video_channel_users", guild.maxVideoChannelUsers);
    map_to_json(j, "approximate_member_count", guild.approximateMemberCount);
    map_to_json(j, "approximate_presence_count", guild.approximatePresenceCount);
    map_to_json(j, "welcome_screen", guild.welcomeScreen);
    j["nsfw_level"] = guild.nsfwLevel;
    map_to_json(j, "stickers", guild.stickers);
    j["premium_progress_bar_enabled"] = guild.premiumProgressBarEnabled;
}

void adb::api::from_json(const nlohmann::json& j, Guild& guild)
{
    j.at("id").get_to(guild.id);
    j.at("name").get_to(guild.name);

    
    map_from_json(j, "icon", guild.icon, [&guild](const nlohmann::json &val) {
        return ImageResolver::getGuildIcon(guild.id, val.get<std::string>());
    });
    map_from_json(j, "icon_hash", guild.iconHash);
    map_from_json(j, "splash", guild.splash, [&guild](const nlohmann::json &val) {
        return ImageResolver::getGuildSplash(guild.id, val.get<std::string>());
    });
    map_from_json(j, "discovery_splash", guild.discoverySplash, [&guild](const nlohmann::json &val) {
        return ImageResolver::getGuildDiscoverySplash(guild.id, val.get<std::string>());
    });

    j.at("owner_id").get_to(guild.ownerId);
    map_from_json(j, "afk_channel_id", guild.afkChannelId);
    j.at("afk_timeout").get_to(guild.afkTimeout);
    map_from_json(j, "widget_enabled", guild.widgetEnabled);
    map_from_json(j, "widget_channel_id", guild.widgetChannelId);
    j.at("verification_level").get_to(guild.verificationLevel);
    j.at("default_message_notifications").get_to(guild.defaultMessageNotifications);
    j.at("explicit_content_filter").get_to(guild.explicitContentFilter);
    j.at("roles").get_to(guild.roles);
    j.at("emojis").get_to(guild.emojis);
    guild.features = transform_to<GuildFeature>(j.at("features").get<std::vector<std::string>>(), [](auto &feature) -> GuildFeature
    {
        GuildFeature f;
        from_string(feature, f);
        return f;
    });
    map_from_json(j, "application_id", guild.applicationId);
    map_from_json(j, "system_channel_id", guild.systemChannelId);
    j.at("system_channel_flags").get_to(guild.systemChannelFlags);
    map_from_json(j, "max_presences", guild.maxPresences);
    map_from_json(j, "max_members", guild.maxMembers);
    map_from_json(j, "vanity_url_code", guild.vanityUrlCode);
    map_from_json(j, "description", guild.description);
    map_from_json(j, "banner", guild.banner, [&guild](const nlohmann::json val) {
        return ImageResolver::getGuildBanner(guild.id, val.get<std::string>());
    });
    j.at("premium_tier").get_to(guild.premiumTier);
    map_from_json(j, "premium_subscription_count", guild.premiumSubscriptionCount);
    from_string(j.at("preferred_locale").get<std::string>(), guild.preferredLocale);
    map_from_json(j, "public_update_channel_id", guild.publicUpdateChannelId);
    map_from_json(j, "max_video_channel_users", guild.maxVideoChannelUsers);
    map_from_json(j, "approximate_member_count", guild.approximateMemberCount);
    map_from_json(j, "approximate_presence_count", guild.approximatePresenceCount);
    map_from_json(j, "welcome_screen", guild.welcomeScreen);
    j.at("nsfw_level").get_to(guild.nsfwLevel);
    map_from_json(j, "stickers", guild.stickers);
    j.at("premium_progress_bar_enabled").get_to(guild.premiumProgressBarEnabled);
}

void adb::api::to_json(nlohmann::json& j, const GuildRelative& guild)
{
    to_json(j, *static_cast<const Guild*>(&guild));
}

void adb::api::from_json(const nlohmann::json& j, GuildRelative& guild)
{
    from_json(j, *static_cast<Guild*>(&guild));
}