#pragma once

#include <string>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>
#include <libadb/api/gateway/data/intents.hpp>

namespace adb::api
{
    /**
     * @brief IdentityConnectionProperties
     * @details https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
     */
    struct IdentityConnectionProperties
    {
        std::string os;
        std::string browser;
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
        std::optional<bool> compress;
        std::optional<uint8_t> largeThresgold;
        // shard
        // presence
        Intents intents;
    };

    LIBADB_API void to_json(nlohmann::json& j, const IdentityConnectionProperties& identity);
    LIBADB_API void from_json(const nlohmann::json& j, IdentityConnectionProperties& identity);

    LIBADB_API void to_json(nlohmann::json& j, const Identity& identity);
    LIBADB_API void from_json(const nlohmann::json& j, Identity& identity);
}