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
            value = obj.is_null() ? value = std::nullopt : obj.get<OptType>();
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
}