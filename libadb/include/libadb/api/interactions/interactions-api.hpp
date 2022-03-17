#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <libadb/api/message/data/send-message.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/api/interactions/data/create-application-command-params.hpp>
#include <libadb/api/interactions/data/application-command.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;

    /**
     * @brief Interactions API
     * @details https://discord.com/developers/docs/interactions/receiving-and-responding#interactions
     */
    class InteractionsApi
    {
        friend DiscordApi;
    public:
        /**
         * @brief Responding to an iteraction with a PONG
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#responding-to-an-interaction
         * @param id Interaction ID, received via Gateway or webhook
         * @param token Interaction token, received via Gateway or webhook
         * @return Was an interaction successefully acknowledged
         */
        LIBADB_API bool ack(const adb::types::SFID &id, const std::string &token);
        /**
         * @brief Responding to an iteraction with a message
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#responding-to-an-interaction
         * @param id Interaction ID, received via Gateway or webhook
         * @param token Interaction token, received via Gateway or webhook
         * @param params Responding message
         * @return Was an interaction successefully responded
         */
        LIBADB_API bool message(const adb::types::SFID &id, const std::string &token, const SendMessageParams &params);
        /**
         * @brief Promise to responding to an iteraction with a message later
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#responding-to-an-interaction
         * @param id Interaction ID, received via Gateway or webhook
         * @param token Interaction token, received via Gateway or webhook
         * @return Was an interaction response successefully promised
         */
        LIBADB_API bool messageLater(const adb::types::SFID &id, const std::string &token);

        /**
         * @brief Edit replayed message
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#edit-original-interaction-response
         * @param appId Application ID
         * @param token Interaction token, received via Gateway or webhook
         * @return std::optional<Message> 
         */
        LIBADB_API std::optional<Message> editReply(const adb::types::SFID &appId, const std::string &token, const SendMessageParams &params);
        /**
         * @brief Create an Application Guild Command
         * @details https://discord.com/developers/docs/interactions/application-commands#create-guild-application-command
         * @param appId Application ID
         * @param guildId Guild ID, where command should be created
         * @param params Command parameters
         * @return true if command created successefully 
         */
        LIBADB_API std::optional<ApplicationCommand> createGuildCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const CreateApplicationCommandParams& params);
        /**
         * @brief Delete an Application Guild Command
         * @details https://discord.com/developers/docs/interactions/application-commands#delete-guild-application-command
         * @param appId Application ID
         * @param guildId Guild ID, where command should be deleted
         * @param commandId Command ID that should be deleted
         * @return true if command deleted successefully  
         */
        LIBADB_API bool deleteGuldCommand(const adb::types::SFID &appId, const adb::types::SFID &guildId, const adb::types::SFID & commandId);
    private:
        InteractionsApi(const std::string &baseUrl);
    private:
        const std::string baseUrl_;
        const std::string webhooksUrl_;
        const std::string appUrl_;
    };
}