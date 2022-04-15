#include <libadb/api/channel/data/followed-channel.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const FollowedChannel& channel)
{
    j = nlohmann::json
    {
        {"channel_id", channel.channelId},
        {"webhook_id", channel.webhookId},
    };
}

void adb::api::from_json(const nlohmann::json& j, FollowedChannel& channel)
{
    j.at("channel_id").get_to(channel.channelId);
    j.at("webhook_id").get_to(channel.webhookId);
}