#include <libadb/api/rate/rate-reader.hpp>
#include <stdexcept>
#include <algorithm>
using namespace adb::api;

namespace
{
    void readImpl(const cpr::Header &header, const std::string key, uint64_t &value);
    void readImpl(const cpr::Header &header, const std::string key, double &value);
    void readImpl(const cpr::Header &header, const std::string key, std::string &value);
    void readImpl(const cpr::Header &header, const std::string key, bool &value);
    void readImpl(const cpr::Header &header, const std::string key, RateLimitScope &value);

    template <typename Type>
    void read(const cpr::Header &header, const std::string key, Type &value)
    {
        if (!header.contains(key))
        {
            throw std::runtime_error("Cannot read " + key);
            return;
        }
        readImpl(header, key, value);
    }

    template <typename Type>
    void read(const cpr::Header &header, const std::string key, std::optional<Type> &value)
    {
        if (!header.contains(key))
        {
            return;
        }
        Type temp;
        readImpl(header, key, temp);
        value = temp;
    }

    void readImpl(const cpr::Header &header, const std::string key, uint64_t &value)
    {
        value = std::atoll(header.at(key).c_str());
    }

    void readImpl(const cpr::Header &header, const std::string key, double &value)
    {
        value = std::atof(header.at(key).c_str());
    }

    void readImpl(const cpr::Header &header, const std::string key, std::string &value)
    {
        value = header.at(key);
    }

    void readImpl(const cpr::Header &header, const std::string key, bool &value)
    {
        value = header.at(key) == "true";
    }

    void readImpl(const cpr::Header &header, const std::string key, RateLimitScope &value)
    {
        from_string(header.at(key), value);
    }
}

bool adb::api::hasRateLimit(const cpr::Header &header)
{
    return std::find_if(header.begin(), header.end(), [](const auto &pair) -> bool
    {
        return pair.first.starts_with("X-RateLimit-");
    }) != header.end();
}

RateLimit adb::api::readRate(const cpr::Header &header)
{
    RateLimit limit;
    read(header, "X-RateLimit-Limit", limit.limit);
    read(header, "X-RateLimit-Remaining", limit.remaining);

    double msReset, msResetAfter;
    read(header, "X-RateLimit-Reset", msReset);
    read(header, "X-RateLimit-Reset-After", msResetAfter);

    adb::types::TimePoint time {};
    time += std::chrono::milliseconds(static_cast<uint64_t>(msReset * 1000));
    limit.reset = time;
    limit.msResetAfter = static_cast<uint64_t>(msResetAfter * 1000);

    read(header, "X-RateLimit-Bucket", limit.bucket);
    read(header, "X-RateLimit-Global", limit.global);
    read(header, "X-RateLimit-Scope", limit.scope);
    return limit;
}