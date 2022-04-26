#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <type_traits>

namespace adb::types::details
{
    template <typename T, typename... Ts>
    constexpr bool have_type_v = (std::is_same_v<T, Ts> || ...);

    template <typename ...VariantTypes>
    concept HaveString = have_type_v<std::string, VariantTypes...>;

    template <typename ...VariantTypes>
    concept DoNotHaveString = !have_type_v<std::string, VariantTypes...>;
}

namespace nlohmann
{
    template <typename ...VariantTypes>
    requires adb::types::details::HaveString<VariantTypes...>
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
    requires adb::types::details::DoNotHaveString<VariantTypes...>
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