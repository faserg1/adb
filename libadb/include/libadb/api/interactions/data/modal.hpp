#pragma once

#include <string>
#include <vector>
#include <memory>
#include <libadb/api/interactions/data/message-component.hpp>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Interaction Modal Response
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-modal
     */
    struct Modal
    {
        /// a developer-defined identifier for the component, max 100 characters
        std::string customId;
        /// the title of the popup modal
        std::string title;
        /// between 1 and 5 (inclusive) components that make up the modal
        std::vector<MessageComponent> components;
    };

    LIBADB_API void to_json(nlohmann::json& j, const Modal& modal);
    LIBADB_API void from_json(const nlohmann::json& j, Modal& modal);
}