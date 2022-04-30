#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/application-flags.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/guild/data/unavailable-guild.hpp>
#include <libadb/api/gateway/data/shard.hpp>
#include <libadb/types/snowflake.hpp>
#include <cstdint>
#include <string>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Ready
     * @details https://discord.com/developers/docs/topics/gateway#ready-ready-event-fields
     */
    struct Ready
    {
        /// gateway version
        uint64_t v;
        /// information about the user including email
        User user;
        /// the guilds the user is in
        std::vector<UnavailableGuild> guilds;
        /// used for resuming connections
        std::string sessionId;
        /// the shard information associated with this session, if sent when identifying
        std::optional<ShardInfo> shard;
        /// application `id` and `flags`
        struct
        {
            adb::types::SFID id;
            ApplicationFlags flags;
        } application;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Ready& ready);
    LIBADB_API void from_json(const nlohmann::json& j, Ready& ready);
}
