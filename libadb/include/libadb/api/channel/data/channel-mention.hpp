#pragma once

#include <optional>
#include <string>
#include <libadb/types/snowflake.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/channel/data/channel-type.hpp>

namespace adb::api
{
    /**
     * @brief Channel Mention Object
     * @details https://discord.com/developers/docs/resources/channel#channel-mention-object
     */
    struct ChannelMention
    {
        /// id of the channel
        adb::types::SFID id;
        /// id of the guild containing the channel
        adb::types::SFID guildId;
        /// the type of channel
        ChannelType type;
        /// the name of the channel
        std::string name;
    };

    void to_json(nlohmann::json& j, const ChannelMention& mention);
    void from_json(const nlohmann::json& j, ChannelMention& mention);
}