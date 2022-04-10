#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/sticker/data/sticker-format.hpp>
#include <libadb/api/sticker/data/sticker-type.hpp>
#include <libadb/api/user/data/user.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <string>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Sticker
     * @details https://discord.com/developers/docs/resources/sticker#sticker-object
     */
    struct Sticker
    {
        /// id of the sticker
        adb::types::SFID id;
        /// for standard stickers, id of the pack the sticker is from
        std::optional<adb::types::SFID> packId;
        /// name of the sticker
        std::string name;
        /// description of the sticker
        adb::types::Nullable<std::string> description;
        /// autocomplete/suggestion tags for the sticker (max 200 characters)
        std::vector<std::string> tags;
        /// type of sticker
        StickerType type;
        /// type of sticker format
        StickerFormat formatType;
        /// whether this guild sticker can be used, may be false due to loss of Server Boosts
        std::optional<bool> available;
        /// id of the guild that owns this sticker
        std::optional<adb::types::SFID> guildId;
        /// the user that uploaded the guild sticker
        std::optional<User> user;
        /// the standard sticker's sort order within its pack
        std::optional<int64_t> sortValue;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Sticker& sticker);
    LIBADB_API void from_json(const nlohmann::json& j, Sticker& sticker);
}