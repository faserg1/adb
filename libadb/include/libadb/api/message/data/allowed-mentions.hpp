#pragma once

#include <libadb/types/snowflake.hpp>
#include <vector>
#include <optional>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/helpers/enums.hpp>

namespace adb::api
{
    /**
     * @brief A bitmask for allowed mention types, replacing array of strings
     * @details https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mention-types
     */
    enum class AllowedMentionsType : uint32_t
    {
        None = 0,
        Roles = (1 << 0),
        Users = (1 << 1),
        Everyone = (1 << 2)
    };

    ADB_ENUM_FLAGS_OPERATORS(AllowedMentionsType, AllowedMentionsTypes, uint32_t)

    /**
     * @brief Allowed Mention Object
     * @details https://discord.com/developers/docs/resources/channel#allowed-mentions-object
     */
    struct AllowedMentions
    {
        /// Bit mask of types to parse from the content
        /// Original: An <string> array of allowed mention types to parse from the content.
        AllowedMentionsType parse;
        /// Array of role_ids to mention (Max size of 100)
        std::optional<std::vector<adb::types::SFID>> roles;
        /// Array of user_ids to mention (Max size of 100)
        std::optional<std::vector<adb::types::SFID>> users;
        /// For replies, whether to mention the author of the message being replied to (default false)
        std::optional<bool> repliedUser;
    };

    void to_json(nlohmann::json& j, const AllowedMentions& allowedMention);
    void from_json(const nlohmann::json& j, AllowedMentions& allowedMention);
}