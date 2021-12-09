#include "guild-member.hpp"
#include <nlohmann/json.hpp>
#include <types/helpers/json-optional.hpp>
#include <types/helpers/json-enum.hpp>
#include <types/helpers/json-chrono.hpp>
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
    map_from_json(j, "avatar", guildMember.avatarHash);
    j.at("roles").get_to(guildMember.roleIds);
    j.at("joined_at").get_to(guildMember.joinedAt);
    map_from_json(j, "premium_since", guildMember.premiumSince);
    j.at("deaf").get_to(guildMember.deaf);
    j.at("mute").get_to(guildMember.mute);
    map_from_json(j, "pending", guildMember.pending);
    map_from_json(j, "permissions", guildMember.permissions);
    map_from_json(j, "communication_disabled_until", guildMember.communicationDisabledUntil);
}