#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <libadb/types/nullable.hpp>
namespace nlohmann
{
    template <class OptType>
    struct adl_serializer<adb::types::Nullable<OptType>>
    {
        static void to_json(json& obj, const adb::types::Nullable<OptType> &value)
        {
            if (value)
                obj = *value;
            else
                obj = nullptr;
        }

        static void from_json(const json& obj, adb::types::Nullable<OptType> &value)
        {
            if (obj.is_null())
                value = nullptr;
            else
                value = obj.get<OptType>();
        }
    };
}

namespace adb::types
{
    template <typename OptType>
    static void map_to_json(nlohmann::json &j, const std::string &key, const adb::types::Nullable<OptType> &value)
    {
        if (value)
            j[key] = *value;
        else
            j[key] = nullptr;
    }

    template <typename OptType>
    static void map_from_json(const nlohmann::json &j, const std::string &key, adb::types::Nullable<OptType> &value)
    {
        if (j.contains(key) && !j.at(key).is_null())
        {
            value = j.at(key).get<OptType>();
        }
    }

    template <typename OptType, typename Resolver>
    static void map_from_json(const nlohmann::json &j, const std::string &key, adb::types::Nullable<OptType> &value, Resolver func)
    {
        if (j.contains(key) && !j.at(key).is_null())
        {
            value = func(j.at(key));
        }
    }
}