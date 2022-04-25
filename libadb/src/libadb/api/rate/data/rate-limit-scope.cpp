#include <libadb/api/rate/data/rate-limit-scope.hpp>
#include <stdexcept>
using namespace adb::api;

void adb::api::from_string(const std::string &str, RateLimitScope &limit)
{
    if (str == "user")
        limit = RateLimitScope::User;
    else if (str == "global")
        limit = RateLimitScope::Global;
    else if (str == "shared")
        limit = RateLimitScope::Shared;
    else
        throw std::runtime_error("Unknown RateLimitScope");
}

std::string adb::api::to_string(RateLimitScope limit)
{
    switch (limit)
    {
        case RateLimitScope::User:
            return "user";
        case RateLimitScope::Global:
            return "global";
        case RateLimitScope::Shared:
            return "shared";
    }
    throw std::runtime_error("Unknown RateLimitScope");
}