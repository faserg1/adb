#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json_fwd.hpp>

#include <libadb/libadb.hpp>

namespace adb::types
{
    /**
     * @brief Snowflake ID
     * @details https://discord.com/developers/docs/reference#snowflakes
     */
    class SFID
    {
    public:
        LIBADB_API SFID();
        LIBADB_API SFID(uint64_t id);
        LIBADB_API SFID(const std::string &strId);

        LIBADB_API SFID(const SFID &other) = default;

        LIBADB_API static SFID create();

        LIBADB_API operator uint64_t() const;
        LIBADB_API operator bool() const;
        LIBADB_API bool operator==(const SFID &other) const;
        LIBADB_API std::string to_string() const;
    private:
        union
        {
            struct
            {
                unsigned long long timestamp : 42;
                unsigned long long internalWorkerId : 5;
                unsigned long long internalProcessId : 5;
                unsigned long long incremental : 12;
            } idParts_;
            uint64_t id_;
        };
    };

    LIBADB_API void to_json(nlohmann::json& j, const SFID& id);
    LIBADB_API void from_json(const nlohmann::json& j, SFID& id);
}