#pragma once

#include <optional>
#include <vector>
#include <libadb/api/user/data/user.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Emoji Object
     * @details https://discord.com/developers/docs/resources/emoji#emoji-object
     */
    struct Emoji
    {
        /// emoji id
        /// @details https://discord.com/developers/docs/reference#image-formatting
        std::optional<adb::types::SFID> id;
        /// emoji name
        std::optional<std::string> name;
        /// roles allowed to use this emoji
        std::optional<std::vector<adb::types::SFID>> roleIds;
        /// user that created this emoji
        std::optional<User> user;
        /// whether this emoji must be wrapped in colons
        std::optional<bool> requireColons;
        /// whether this emoji is managed
        std::optional<bool> managed;
        /// whether this emoji is animated
        std::optional<bool> animated;
        /// whether this emoji can be used, may be false due to loss of Server Boosts
        std::optional<bool> available;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Emoji& emoji);
    LIBADB_API void from_json(const nlohmann::json& j, Emoji& emoji);
}