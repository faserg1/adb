#pragma once

#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief 
     * @details https://discord.com/developers/docs/topics/teams#data-models-team-object
     */
    struct Team
    {
        
    };

    LIBADB_API void to_json(nlohmann::json& j, const Team& team);
    LIBADB_API void from_json(const nlohmann::json& j, Team& team);
}