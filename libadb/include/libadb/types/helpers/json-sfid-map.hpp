#pragma once

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <libadb/types/snowflake.hpp>

namespace nlohmann
{
    template <typename ValueType>
    struct adl_serializer<std::unordered_map<adb::types::SFID, ValueType>>
    {
        static void to_json(json& obj, const std::unordered_map<adb::types::SFID, ValueType> &value)
        {
            for (const auto &pair : value)
            {
                obj[pair.first.to_string()] = pair.second;
            }
        }

        static void from_json(const json& obj, std::unordered_map<adb::types::SFID, ValueType> &value)
        {
            for (const auto &element : obj.items())
            {
                value.insert_or_assign(adb::types::SFID{element.key()}, element.value().get<ValueType>());
            }
        }
    };
}