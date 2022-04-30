#include <libadb/api/gateway/data/shard.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const ShardInfo& shardInfo)
{
    j = nlohmann::json {shardInfo.shardId, shardInfo.numShards};
}

void adb::api::from_json(const nlohmann::json& j, ShardInfo& shardInfo)
{
    j.at(0).get_to(shardInfo.shardId);
    j.at(1).get_to(shardInfo.numShards);
}