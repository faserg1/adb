#pragma once

#include <memory>
#include <libadb/libadb.hpp>
#include <libadb/api/interactions/data/message-component-type.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Base for Message Components
     * @details https://discord.com/developers/docs/interactions/message-components#component-object
     */
    struct MessageComponentBase
    {
        using Origin = MessageComponentBase;
        /// Type of component
        MessageComponentType type;
    };

    using MessageComponent = std::shared_ptr<MessageComponentBase>;

    LIBADB_API void to_json(nlohmann::json& j, const std::shared_ptr<MessageComponentBase>& mc);
    LIBADB_API void from_json(const nlohmann::json& j, std::shared_ptr<MessageComponentBase>& mc);
}