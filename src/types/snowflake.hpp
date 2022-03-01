#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace adb::types
{
    /**
     * @brief Snowflake ID
     * @details https://discord.com/developers/docs/reference#snowflakes
     */
    class SFID
    {
    public:
        SFID() = default;
        SFID(uint64_t id);
        SFID(const std::string &strId);

        SFID(const SFID &other) = default;

        SFID create();

        inline operator uint64_t() const { return id_; }
        std::string to_string() const;
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

    void to_json(nlohmann::json& j, const SFID& id);
    void from_json(const nlohmann::json& j, SFID& id);
}