#include <libadb/api/guild/data/guild-member.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/resource/image-resolver.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const GuildMember& guildMember)
{
    j = nlohmann::json
    {
    };
}

void adb::api::from_json(const nlohmann::json& j, GuildMember& guildMember)
{
    map_from_json(j, "user", guildMember.user);
    map_from_json(j, "nick", guildMember.nick);
    if (j.contains("avatar"))
    {
        std::string hash;
        j.at("avatar").get_to(hash);
        adb::types::SFID userId;
        if (guildMember.user.has_value())
            userId = guildMember.user.value().id;
        // avatar will be parsed in another function
        guildMember.avatar = std::make_shared<adb::resource::Image>(
            adb::resource::ImageResolver::getGuildMemberAvatar({}, userId, hash));
    }
    j.at("roles").get_to(guildMember.roleIds);
    j.at("joined_at").get_to(guildMember.joinedAt);
    map_from_json(j, "premium_since", guildMember.premiumSince);
    j.at("deaf").get_to(guildMember.deaf);
    j.at("mute").get_to(guildMember.mute);
    map_from_json(j, "pending", guildMember.pending);
    map_from_json(j, "permissions", guildMember.permissions);
    map_from_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}

void adb::api::gm_parse_avatar(adb::types::SFID guildId, std::optional<adb::types::SFID> optUserId,
    const nlohmann::json& jGuildMember, GuildMember& guildMember)
{
    if (jGuildMember.contains("avatar"))
    {
        std::string hash;
        jGuildMember.at("avatar").get_to(hash);
        adb::types::SFID userId;
        if (guildMember.user.has_value())
            userId = guildMember.user.value().id;
        else if (optUserId.has_value())
            userId = optUserId.value();
        guildMember.avatar = std::make_shared<adb::resource::Image>(
            adb::resource::ImageResolver::getGuildMemberAvatar(guildId, userId, hash));
    }
}