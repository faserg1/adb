#include <libadb/api/user/data/user.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/resource/image-resolver.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const User& user)
{
    j = nlohmann::json
    {
        {"id", user.id},
        {"username", user.username},
        {"discriminator", user.discriminator},
        {"bot", user.bot},
        {"system", user.system},
        {"mfa_enabled", user.mfaEnabled},
        {"accent_color", user.accentColor},
        {"verified", user.verified},
        {"email", user.email},
        {"flags", user.flags},
        {"premium_type", user.premiumType},
        {"public_flags", user.publicFlags}
    };
    map_to_json(j, "avatar", user.avatar);
    map_to_json(j, "banner", user.banner);

    if (user.locale.has_value())
    {
        j["locale"] = adb::resource::to_string(user.locale.value());
    }
}

void adb::api::from_json(const nlohmann::json& j, User& user)
{
    j.at("id").get_to(user.id);
    j.at("username").get_to(user.username);
    j.at("discriminator").get_to(user.discriminator);
    map_from_json(j, "avatar", user.avatar, [&user](const nlohmann::json &val)
    {
        return adb::resource::ImageResolver::getUserAvarar(user.id, val.get<std::string>());
    });
    map_from_json(j, "bot", user.bot);
    map_from_json(j, "system", user.system);
    map_from_json(j, "mfa_enabled", user.mfaEnabled);
    map_from_json(j, "banner", user.avatar, [&user](const nlohmann::json &val)
    {
        return adb::resource::ImageResolver::getUserBanner(user.id, val.get<std::string>());
    });
    map_from_json(j, "accent_color", user.accentColor);
    if (j.contains("locale"))
    {
        std::string str;
        j.at("locale").get_to(str);
        adb::resource::Locale locale;
        adb::resource::from_string(str, locale);
        user.locale = locale;
    }
    
    map_from_json(j, "verified", user.verified);
    map_from_json(j, "email", user.email);
    map_from_json(j, "flags", user.flags);
    map_from_json(j, "premium_type", user.premiumType);
    map_from_json(j, "public_flags", user.publicFlags);
}