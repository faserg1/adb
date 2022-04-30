#pragma once

#include <libadb/libadb.hpp>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Shard Info
     * @details https://discord.com/developers/docs/topics/gateway#sharding
     */
    struct ShardInfo
    {
        /// The ID of the current shard
        uint64_t shardId;
        /// Number of the shards
        uint64_t numShards;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ShardInfo& shardInfo);
    LIBADB_API void from_json(const nlohmann::json& j, ShardInfo& shardInfo);
}