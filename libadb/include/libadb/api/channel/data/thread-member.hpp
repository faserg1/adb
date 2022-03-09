#pragma once

#include <optional>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/time.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Thread Member
     * @details https://discord.com/developers/docs/resources/channel#thread-member-object
     */
    struct ThreadMember
    {
        /// the id of the thread
        std::optional<adb::types::SFID> id;
        /// the id of the user
        std::optional<adb::types::SFID> userId;
        /// the time the current user last joined the thread
        adb::types::TimePoint joinTimestamp;
        /// any user-thread settings, currently only used for notifications
        size_t flags;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ThreadMember& member);
    LIBADB_API void from_json(const nlohmann::json& j, ThreadMember& member);
}