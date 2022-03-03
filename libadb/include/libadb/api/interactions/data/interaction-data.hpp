#pragma once

#include <libadb/types/snowflake.hpp>
#include <optional>
#include <vector>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/message/data/message-component-type.hpp>
#include <libadb/api/interactions/data/application-command-type.hpp>

namespace adb::api
{
    /**
     * @brief Interaction Data Structure
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
     */
    struct InteractionData
    {

    };

    
    struct InteractionDataApplicationCommand : InteractionData
    {
        /**
         * @brief the ID of the invoked command
         * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
         */
        adb::types::SFID id;
        /**
         * @brief the name of the invoked command
         * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
         */
        std::string name;
        /**
         * @brief the type of the invoked command
         * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-structure
         */
        ApplicationCommandType type;
    };

    struct InteractionDataComponent : InteractionData
    {
        std::optional<std::string> customId; ///< the custom_id of the component
        MessageComponentType componentType; ///< the type of the component
        std::optional<std::vector<std::string>> values; ///< the values the user selected
    };

    void to_json(nlohmann::json& j, const InteractionDataApplicationCommand& appCommand);
    void from_json(const nlohmann::json& j, InteractionDataApplicationCommand& appCommand);

    void to_json(nlohmann::json& j, const InteractionDataComponent& dataComponent);
    void from_json(const nlohmann::json& j, InteractionDataComponent& dataComponent);
}