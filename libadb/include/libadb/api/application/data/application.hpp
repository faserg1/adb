#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/application/data/application-flags.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief 
     * @details 
     */
    struct Application
    {

    };

    LIBADB_API void to_json(nlohmann::json& j, const Application& app);
    LIBADB_API void from_json(const nlohmann::json& j, Application& app);
}