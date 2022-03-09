#include <libadb/api/channel/data/thread-member.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ThreadMember& member)
{
    j = nlohmann::json
    {
        {"id", member.id},
        {"user_id", member.userId},
        {"join_timestamp", member.joinTimestamp},
        {"flags", member.flags},
    };
}

void adb::api::from_json(const nlohmann::json& j, ThreadMember& member)
{
    map_from_json(j, "id", member.id);
    map_from_json(j, "user_id", member.userId);
    j.at("join_timestamp").get_to(member.joinTimestamp);
    j.at("flags").get_to(member.flags);
}