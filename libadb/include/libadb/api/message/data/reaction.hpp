#pragma once

#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/emoji/data/emoji.hpp>

namespace adb::api
{
    /**
     * @brief Message Reaction
     * @details https://discord.com/developers/docs/resources/channel#reaction-object
     */
    struct Reaction
    {
        /// times this emoji has been used to react
        size_t count;
        /// whether the current user reacted using this emoji
        bool me;
        /// emoji information
        Emoji emoji;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Reaction& reaction);
    LIBADB_API void from_json(const nlohmann::json& j, Reaction& reaction);
}