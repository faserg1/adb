#include <libadb/api/message/data/message-activity.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const MessageActivity& activity)
{
    j = nlohmann::json
    {
        {"type", activity.type},
        {"party_id", activity.partyId}
    };
}

void adb::api::from_json(const nlohmann::json& j, MessageActivity& activity)
{
    j.at("type").get_to(activity.type);
    map_from_json(j, "party_id", activity.partyId);
}