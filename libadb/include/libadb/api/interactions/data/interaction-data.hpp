#pragma once

#include <libadb/types/snowflake.hpp>
#include <optional>
#include <vector>
#include <type_traits>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/interactions/data/message-component.hpp>
#include <libadb/api/interactions/data/application-command-type.hpp>
#include <libadb/api/interactions/data/resolved-data.hpp>
#include <libadb/api/interactions/data/interaction-data-command-option.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    /**
     * @brief Interaction Data Structure
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
     */
    struct InteractionData
    {

    };

    template<class InteractionDataType>
    concept InteractionDataBase = std::is_base_of_v<InteractionData, InteractionDataType>;
    
    struct InteractionDataApplicationCommand : InteractionData
    {
        /// the ID of the invoked command
        adb::types::SFID id;
        /// the name of the invoked command
        std::string name;
        /// the type of the invoked command
        ApplicationCommandType type;
        /// converted users + roles + channels + attachments
        std::optional<ResolvedData> resolved;
        /// the params + values from the user
        std::optional<std::vector<InteractionDataCommandOption>> options;
        /// the id of the guild the command is registered to
        std::optional<adb::types::SFID> guildId;
    };

    struct InteractionDataComponent : InteractionData
    {
        /// the custom_id of the component
        std::optional<std::string> customId;
        /// the type of the component
        MessageComponentType componentType;
        /// the values the user selected
        std::optional<std::vector<std::string>> values;
    };

    struct InteractionDataModal : InteractionData
    {
        /// the custom_id of the component
        std::optional<std::string> customId;
        /// the values submitted by the user
        std::optional<std::vector<MessageComponent>> components;
    };

    LIBADB_API void to_json(nlohmann::json& j, const InteractionDataApplicationCommand& appCommand);
    LIBADB_API void from_json(const nlohmann::json& j, InteractionDataApplicationCommand& appCommand);

    LIBADB_API void to_json(nlohmann::json& j, const InteractionDataComponent& dataComponent);
    LIBADB_API void from_json(const nlohmann::json& j, InteractionDataComponent& dataComponent);

    LIBADB_API void to_json(nlohmann::json& j, const InteractionDataModal& modal);
    LIBADB_API void from_json(const nlohmann::json& j, InteractionDataModal& modal);
}