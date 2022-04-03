#include <libadb/api/guild/data/guild-member-update.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/resource/image-resolver.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const GuildMemberUpdate& guildMemberUpdate)
{
    j = nlohmann::json
    {
        {"guild_id", guildMemberUpdate.guildId},
        {"roles", guildMemberUpdate.roleIds},
        {"user", guildMemberUpdate.user},
    };
    map_to_json(j, "nick", guildMemberUpdate.nick);
    j["avatar"] = guildMemberUpdate.avatar ? guildMemberUpdate.avatar->getName() : nullptr;
    map_to_json(j, "joined_at", guildMemberUpdate.joinedAt);
    map_to_json(j, "premium_since", guildMemberUpdate.premiumSince);
    map_to_json(j, "deaf", guildMemberUpdate.deaf);
    map_to_json(j, "mute", guildMemberUpdate.mute);
    map_to_json(j, "pending", guildMemberUpdate.pending);
    map_to_json(j, "communication_disabled_until", guildMemberUpdate.communicationDisabledUntil);
}

void adb::api::from_json(const nlohmann::json& j, GuildMemberUpdate& guildMemberUpdate)
{
    j.at("guild_id").get_to(guildMemberUpdate.guildId);
    j.at("roles").get_to(guildMemberUpdate.roleIds);
    j.at("user").get_to(guildMemberUpdate.user);
    map_from_json(j, "nick", guildMemberUpdate.nick);
    if (j.contains("avatar"))
    {
        auto guildId = guildMemberUpdate.guildId;
        auto userId = guildMemberUpdate.user.id;
        auto hash = j.at("avatar").get<std::string>();
        guildMemberUpdate.avatar = std::make_shared<adb::resource::Image>(
            adb::resource::ImageResolver::getGuildMemberAvatar(guildId, userId, hash));
    }
    map_from_json(j, "joined_at", guildMemberUpdate.joinedAt);
    map_from_json(j, "premium_since", guildMemberUpdate.premiumSince);
    map_from_json(j, "deaf", guildMemberUpdate.deaf);
    map_from_json(j, "mute", guildMemberUpdate.mute);
    map_from_json(j, "pending", guildMemberUpdate.pending);
    map_from_json(j, "communication_disabled_until", guildMemberUpdate.communicationDisabledUntil);
}