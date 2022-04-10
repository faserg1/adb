#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <optional>

namespace nlohmann
{
    template <typename OptType>
    struct adl_serializer<std::optional<OptType>>
    {
        static void to_json(json& obj, const std::optional<OptType> &value)
        {
            if (value.has_value())
                obj = value.value();
        }

        static void from_json(const json& obj, std::optional<OptType> &value)
        {
            if (obj.is_null())
                value = std::nullopt;
            else
                value = obj.get<OptType>();
        }
    };
}

namespace adb::types
{
    template <typename OptType>
    static void map_to_json(nlohmann::json &j, const std::string &key, const std::optional<OptType> &value)
    {
        if (value.has_value())
            j[key] = value.value();
    }

    template <typename OptType>
    static void map_from_json(const nlohmann::json &j, const std::string &key, std::optional<OptType> &value)
    {
        if (j.contains(key) && !j.at(key).is_null())
        {
            OptType v {};
            j.at(key).get_to(v);
            value = std::move(v);
        }
    }

    template <typename OptType, typename Resolver>
    static void map_from_json(const nlohmann::json &j, const std::string &key, std::optional<OptType> &value, Resolver func)
    {
        if (j.contains(key) && !j.at(key).is_null())
        {
            OptType v {};
            v = func(j.at(key));
            value = std::move(v);
        }
    }
}