#pragma once

#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Media Stream Description
     * 
     * [NOT DOCUMENTED!!!]
     */
    struct MediaStreamDescription
    {

    };

    LIBADB_API void to_json(nlohmann::json& j, const MediaStreamDescription& desc);
    LIBADB_API void from_json(const nlohmann::json& j, MediaStreamDescription& desc);
}