#include <libadb/api/channel/data/channel.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/resource/image-resolver.hpp>

using namespace adb::api;
using namespace adb::types;
using namespace adb::resource;

void adb::api::to_json(nlohmann::json& j, const Channel& channel)
{
    j = nlohmann::json
    {
        {"id", channel.id},
    };
}

void adb::api::from_json(const nlohmann::json& j, Channel& channel)
{
    j.at("id").get_to(channel.id);
    j.at("type").get_to(channel.type);
    map_from_json(j, "guild_id", channel.guildId);
    map_from_json(j, "position", channel.position);
    map_from_json(j, "permission_overwrites", channel.permissionOverwrites);
    map_from_json(j, "name", channel.name);
    map_from_json(j, "topic", channel.topic);
    map_from_json(j, "nsfw", channel.nsfw);
    map_from_json(j, "last_message_id", channel.lastMessageId);
    map_from_json(j, "bitrate", channel.bitrate);
    map_from_json(j, "user_limit", channel.userLimit);
    map_from_json(j, "rate_limit_per_user", channel.rateLimitPerUser);
    map_from_json(j, "recipients", channel.recipients);

    map_from_json(j, "icon", channel.icon, [](const nlohmann::json &val) {
        return ImageResolver::getGroupDMIcon(val.get<std::string>());
    });

    map_from_json(j, "owner_id", channel.ownerId);
    map_from_json(j, "application_id", channel.applicationId);
    map_from_json(j, "parent_id", channel.parentId);
    map_from_json(j, "last_pin_timestamp", channel.lastPinTimestamp);
    map_from_json(j, "rtc_region", channel.rtcRegion);
    map_from_json(j, "video_quality_mode", channel.videoQualityMode);
    map_from_json(j, "message_count", channel.messageCount);
    map_from_json(j, "member_count", channel.memberCount);
    map_from_json(j, "thread_metadata", channel.threadMetadata);
    map_from_json(j, "member", channel.threadMember);
    map_from_json(j, "defailt_auto_archive_duration", channel.defailtAutoArchiveDuration);
    std::optional<std::string> strPermissions;
    map_from_json(j, "permissions", strPermissions);
    if (strPermissions.has_value())
    {
        Permissions permissions;
        adb::api::from_string(strPermissions.value(), permissions);
        channel.permissions = permissions;
    }
}