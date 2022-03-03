#include <libadb/api/user/data/user.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-enum.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const User& user)
{
    j = nlohmann::json
    {
        {"id", user.id},
        {"username", user.username},
        {"discriminator", user.discriminator},
        {"avatar", user.avatarHash},
        {"bot", user.bot},
        {"system", user.system},
        {"mfa_enabled", user.mfaEnabled},
        {"banner", user.bannerHash},
        {"accent_color", user.accentColor},
        {"locale", user.locale},
        {"verified", user.verified},
        {"email", user.email},
        {"flags", user.flags},
        {"premium_type", user.premiumType},
        {"public_flags", user.publicFlags}
    };
}

void adb::api::from_json(const nlohmann::json& j, User& user)
{
    j.at("id").get_to(user.id);
    j.at("username").get_to(user.username);
    j.at("discriminator").get_to(user.discriminator);
    if (!j.at("avatar").is_null())
        j.at("avatar").get_to(user.avatarHash);
    if (j.contains("bot"))
        j.at("bot").get_to(user.bot);
    if (j.contains("system"))
        j.at("system").get_to(user.system);
    if (j.contains("mfa_enabled"))
        j.at("mfa_enabled").get_to(user.mfaEnabled);
    if (j.contains("banner") && !j.at("banner").is_null())
        j.at("banner").get_to(user.bannerHash);
    if (j.contains("accent_color") && !j.at("accent_color").is_null())
        j.at("accent_color").get_to(user.accentColor);
    if (j.contains("locale"))
        j.at("locale").get_to(user.locale);
    if (j.contains("verified"))
        j.at("verified").get_to(user.verified);
    if (j.contains("email") && !j.at("email").is_null())
        j.at("email").get_to(user.email);
    if (j.contains("flags"))
        j.at("flags").get_to(user.flags);
    if (j.contains("premium_type"))
        j.at("premium_type").get_to(user.premiumType);
    if (j.contains("public_flags"))
        j.at("public_flags").get_to(user.publicFlags);
}