#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/api/gateway/data/intents.hpp>
#include <libadb/api/gateway/data/shard.hpp>
namespace adb::api
{
    /**
     * @brief IdentityConnectionProperties
     * @details https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
     */
    struct IdentityConnectionProperties
    {
        /// your operating system
        std::string os;
        /// your library name
        std::string browser;
        /// your library name
        std::string device;
    };

    /**
     * @brief Identify Structure
     * @details https://discord.com/developers/docs/topics/gateway#identify-identify-structure
     */
    struct Identity
    {
        /// authentication token
        std::string token;
        /// connection properties
        IdentityConnectionProperties properties;
        /// whether this connection supports compression of packets
        std::optional<bool> compress;
        /// value between 50 and 250, total number of members where the gateway will stop sending offline members in the guild member list
        std::optional<uint8_t> largeThresgold;
        /// used for Guild Sharding
        std::optional<ShardInfo> shard;
        // presence
        /// the Gateway Intents you wish to receive
        Intents intents;
    };

    LIBADB_API void to_json(nlohmann::json& j, const IdentityConnectionProperties& identity);
    LIBADB_API void from_json(const nlohmann::json& j, IdentityConnectionProperties& identity);

    LIBADB_API void to_json(nlohmann::json& j, const Identity& identity);
    LIBADB_API void from_json(const nlohmann::json& j, Identity& identity);
}