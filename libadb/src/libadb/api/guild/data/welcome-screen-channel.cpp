#include <libadb/api/guild/data/welcome-screen-channel.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const WelcomeScreenChannel& channel)
{
    j = nlohmann::json
    {
        {"channel_id", channel.channelId},
        {"description", channel.description}
    };
    map_to_json(j, "emoji_id", channel.emojiId);
    map_to_json(j, "emoji_name", channel.emojiName);
}

void adb::api::from_json(const nlohmann::json& j, WelcomeScreenChannel& channel)
{
    j.at("channel_id").get_to(channel.channelId);
    j.at("description").get_to(channel.description);
    map_from_json(j, "emoji_id", channel.emojiId);
    map_from_json(j, "emoji_name", channel.emojiName);
}