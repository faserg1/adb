#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <libadb/types/time.hpp>
#include <libadb/api/rate/data/rate-limit-scope.hpp>

namespace adb::api
{
    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/rate-limits#header-format
     */
    struct RateLimit
    {
        /// The number of requests that can be made
        uint64_t limit;
        /// The number of remaining requests that can be made
        uint64_t remaining;
        /// Time at which the rate limit resets
        adb::types::TimePoint reset;
        /// Total time (in milliseconds) of when the current rate limit bucket will reset. 
        uint64_t msResetAfter;
        /// A unique string denoting the rate limit being encountered (non-inclusive of top-level resources in the path)
        std::string bucket;
        /// Returned only on HTTP 429 responses if the rate limit encountered is the global rate limit (not per-route)
        std::optional<bool> global;
        /// Returned only on HTTP 429 responses.
        std::optional<RateLimitScope> scope;
    };
}