#include <libadb/api/guild/data/guild-member.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/resource/image-resolver.hpp>
using namespace adb::api;
using namespace adb::types;
using namespace adb::resource;

void adb::api::to_json(nlohmann::json& j, const GuildMember& guildMember)
{
    j = nlohmann::json {};
    map_to_json(j, "user", guildMember.user);
    map_to_json(j, "nick", guildMember.nick);
    if (guildMember.avatar.has_value())
    {
        if (guildMember.avatar.value())
            j["avatar"] = guildMember.avatar.value()->getName();
        else
            j["avatar"] = nullptr;
    }
    j["roles"] = guildMember.roleIds;
    j["joined_at"] = guildMember.joinedAt;
    map_to_json(j, "premium_since", guildMember.premiumSince);
    j["deaf"] = guildMember.deaf;
    j["mute"] = guildMember.mute;
    map_to_json(j, "pending", guildMember.pending);
    std::optional<std::string> strPermissions;
    if (guildMember.permissions.has_value())
    {
        strPermissions = adb::api::to_string(guildMember.permissions.value());
    }
    map_to_json(j, "permissions", strPermissions);
    map_to_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}

void adb::api::from_json(const nlohmann::json& j, GuildMember& guildMember)
{
    map_from_json(j, "user", guildMember.user);
    map_from_json(j, "nick", guildMember.nick);
    map_from_json(j, "avatar", guildMember.avatar, [&guildMember](const nlohmann::json &val) {
        adb::types::SFID userId;
        if (guildMember.user.has_value())
            userId = guildMember.user.value().id;
        return ImageResolver::getGuildMemberAvatar({}, userId, val.get<std::string>());
    });
    j.at("roles").get_to(guildMember.roleIds);
    j.at("joined_at").get_to(guildMember.joinedAt);
    map_from_json(j, "premium_since", guildMember.premiumSince);
    j.at("deaf").get_to(guildMember.deaf);
    j.at("mute").get_to(guildMember.mute);
    map_from_json(j, "pending", guildMember.pending);
    std::optional<std::string> strPermissions;
    map_from_json(j, "permissions", strPermissions);
    if (strPermissions.has_value())
    {
        Permissions permissions;
        adb::api::from_string(strPermissions.value(), permissions);
        guildMember.permissions = permissions;
    }
    map_from_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}

void adb::api::gm_parse_avatar(adb::types::SFID guildId, std::optional<adb::types::SFID> optUserId,
    const nlohmann::json& jGuildMember, GuildMember& guildMember)
{
    map_from_json(jGuildMember, "avatar", guildMember.avatar, [&guildId, &guildMember, &optUserId](const nlohmann::json &val) {
        adb::types::SFID userId;
        if (optUserId.has_value())
            userId = optUserId.value();
        return ImageResolver::getGuildMemberAvatar(guildId, userId, val.get<std::string>());
    });
}

void adb::api::to_json(nlohmann::json& j, const PartialGuildMember& guildMember)
{
    j = nlohmann::json {};
    map_to_json(j, "user", guildMember.user);
    map_to_json(j, "nick", guildMember.nick);
    if (guildMember.avatar.has_value())
    {
        if (guildMember.avatar.value())
            j["avatar"] = guildMember.avatar.value()->getName();
        else
            j["avatar"] = nullptr;
    }
    map_to_json(j, "roles", guildMember.roleIds);
    map_to_json(j, "joined_at", guildMember.joinedAt);
    map_to_json(j, "premium_since", guildMember.premiumSince);
    map_to_json(j, "deaf", guildMember.deaf);
    map_to_json(j, "mute", guildMember.mute);
    map_to_json(j, "pending", guildMember.pending);
    std::optional<std::string> strPermissions;
    if (guildMember.permissions.has_value())
    {
        strPermissions = adb::api::to_string(guildMember.permissions.value());
    }
    map_to_json(j, "permissions", strPermissions);
    map_to_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}

void adb::api::from_json(const nlohmann::json& j, PartialGuildMember& guildMember)
{
    map_from_json(j, "user", guildMember.user);
    map_from_json(j, "nick", guildMember.nick);
    map_from_json(j, "avatar", guildMember.avatar, [&guildMember](const nlohmann::json &val) {
        adb::types::SFID userId;
        if (guildMember.user.has_value())
            userId = guildMember.user.value().id;
        return ImageResolver::getGuildMemberAvatar({}, userId, val.get<std::string>());
    });
    map_from_json(j, "roles", guildMember.roleIds);
    map_from_json(j, "joined_at", guildMember.joinedAt);
    map_from_json(j, "premium_since", guildMember.premiumSince);
    map_from_json(j, "deaf", guildMember.deaf);
    map_from_json(j, "mute", guildMember.mute);
    map_from_json(j, "pending", guildMember.pending);
    std::optional<std::string> strPermissions;
    map_from_json(j, "permissions", strPermissions);
    if (strPermissions.has_value())
    {
        Permissions permissions;
        adb::api::from_string(strPermissions.value(), permissions);
        guildMember.permissions = permissions;
    }
    map_from_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}