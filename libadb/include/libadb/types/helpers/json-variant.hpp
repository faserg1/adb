#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <type_traits>

namespace nlohmann
{
    template <typename ...VariantTypes>
    concept HasString = std::is_same_v<std::variant<VariantTypes...>, std::variant<std::string, VariantTypes...>>;

    template <typename ...VariantTypes>
    concept NotHasString = !std::is_same_v<std::variant<VariantTypes...>, std::variant<std::string, VariantTypes...>>;

    template <typename ...VariantTypes>
    requires HasString<VariantTypes...>
    struct adl_serializer<std::variant<VariantTypes...>>
    {
        using var_t = std::variant<VariantTypes...>;
        static void to_json(json& obj, const var_t &value)
        {
            std::visit([&obj](auto &val){obj = val;}, value);
        }

        static void from_json(const json& obj, var_t &value)
        {
            
            if (obj.is_number_float())
                value = obj.get<double>();
            else if (obj.is_number())
                value = obj.get<int64_t>();
            else if (obj.is_string())
                value = obj.get<std::string>();
        }
    };

    template <typename ...VariantTypes>
    requires NotHasString<VariantTypes...>
    struct adl_serializer<std::variant<VariantTypes...>>
    {
        using var_t = std::variant<VariantTypes...>;
        static void to_json(json& obj, const var_t &value)
        {
            std::visit([&obj](auto &val){obj = val;}, value);
        }

        static void from_json(const json& obj, var_t &value)
        {
            
            if (obj.is_number_float())
                value = obj.get<double>();
            else if (obj.is_number())
                value = obj.get<int64_t>();
        }
    };
}