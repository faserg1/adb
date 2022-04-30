#pragma once

#include <libadb/libadb.hpp>
#include <cstdint>
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Resume
     * @details https://discord.com/developers/docs/topics/gateway#resume-resume-structure
     */
    struct Resume
    {
        /// session token
        std::string token;
        /// session id
        std::string sessionId;
        /// last sequence number received
        uint64_t seq;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Resume& resume);
    LIBADB_API void from_json(const nlohmann::json& j, Resume& resume);
}
