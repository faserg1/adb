#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <optional>
#include <type_traits>

namespace adb::types::concepts
{
    template <class Type>
    concept EnumType = std::conjunction_v<
        std::is_enum_v<Type>,
        std::negation_v<std::is_same_v<Type, nlohmann::detail::value_t>>
        >;
}

namespace nlohmann
{
    template <adb::types::concepts::EnumType Enum>
    struct adl_serializer<Enum>
    {
        static void to_json(json& j, const Enum &value)
        {
            j = static_cast<std::underlying_type_t<Enum>>(value);
        }

        static void from_json(const json& j, Enum &value)
        {
            if (j.is_string())
            {
                auto tempStr = j.get<std::string>();
                value = static_cast<Enum>(std::atoll(tempStr.data()));
            }
            else
                value = static_cast<Enum>(j.get<std::underlying_type_t<Enum>>());
        }
    };
}