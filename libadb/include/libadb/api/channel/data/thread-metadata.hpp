#pragma once

#include <optional>
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/time.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Thread Metadata
     * @details https://discord.com/developers/docs/resources/channel#thread-metadata-object
     */
    struct ThreadMetadata
    {
        /// whether the thread is archived
        bool archived;
        /// duration in minutes to automatically archive the thread after recent activity, can be set to: 60, 1440, 4320, 10080
        size_t autoArchiveDuration;
        /// timestamp when the thread's archive status was last changed, used for calculating recent activity
        adb::types::TimePoint archiveTimestamp;
        /// whether the thread is locked; when a thread is locked, only users with MANAGE_THREADS can unarchive it
        bool locked;
        /// whether non-moderators can add other non-moderators to a thread; only available on private threads
        std::optional<bool> invitable;
        /// timestamp when the thread was created; only populated for threads created after 2022-01-09
        std::optional<adb::types::Nullable<adb::types::TimePoint>> createTimestamp;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ThreadMetadata& metadata);
    LIBADB_API void from_json(const nlohmann::json& j, ThreadMetadata& metadata);
}