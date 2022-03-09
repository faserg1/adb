#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/sticker/data/sticker-format.hpp>
#include <libadb/types/snowflake.hpp>
#include <string>
#include <nlohmann/json_fwd.hpp>


namespace adb::api
{
    /**
     * @brief Sticker Item
     * @details https://discord.com/developers/docs/resources/sticker#sticker-item-object
     */
    struct StickerItem
    {
        /// id of the sticker
        adb::types::SFID id;
        /// name of the sticker
        std::string name;
        /// type of sticker format
        StickerFormat formatType;
    };

    LIBADB_API void to_json(nlohmann::json& j, const StickerItem& item);
    LIBADB_API void from_json(const nlohmann::json& j, StickerItem& item);
}