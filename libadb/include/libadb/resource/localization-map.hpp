#pragma once

#include <unordered_map>
#include <string>

#include <libadb/libadb.hpp>
#include <libadb/resource/locale.hpp>
#include <nlohmann/json_fwd.hpp>


namespace adb::resource
{
    using LocalizationMap = std::unordered_map<Locale, std::string>;

    LIBADB_API void to_json(nlohmann::json& j, const LocalizationMap& locMap);
    LIBADB_API void from_json(const nlohmann::json& j, LocalizationMap& locMap);
}