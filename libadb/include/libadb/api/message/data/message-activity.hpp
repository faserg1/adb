#pragma once

#include <libadb/libadb.hpp>
#include <libadb/api/message/data/message-activity-type.hpp>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace adb::api
{
    /**
     * @brief Message Activity
     * @details https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure
     */
    struct MessageActivity
    {
        /// type of message activity
        MessageActivityType type;
        /// party_id from a Rich Presence event
        /// @details https://discord.com/developers/docs/rich-presence/how-to#updating-presence-update-presence-payload-fields
        std::optional<adb::types::SFID> partyId;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MessageActivity& activity);
    LIBADB_API void from_json(const nlohmann::json& j, MessageActivity& activity);
}