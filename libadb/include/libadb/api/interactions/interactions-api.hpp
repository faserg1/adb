#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <libadb/api/message/data/send-message.hpp>
#include <libadb/api/message/data/message.hpp>

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
        bool ack(const adb::types::SFID &id, const std::string &token);
        /**
         * @brief Responding to an iteraction with a message
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#responding-to-an-interaction
         * @param id Interaction ID, received via Gateway or webhook
         * @param token Interaction token, received via Gateway or webhook
         * @param params Responding message
         * @return Was an interaction successefully responded
         */
        bool message(const adb::types::SFID &id, const std::string &token, const SendMessageParams &params);
        /**
         * @brief Promise to responding to an iteraction with a message later
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#responding-to-an-interaction
         * @param id Interaction ID, received via Gateway or webhook
         * @param token Interaction token, received via Gateway or webhook
         * @return Was an interaction response successefully promised
         */
        bool messageLater(const adb::types::SFID &id, const std::string &token);

        /**
         * @brief Edit replayed message
         * @details https://discord.com/developers/docs/interactions/receiving-and-responding#edit-original-interaction-response
         * @param token Interaction token, received via Gateway or webhook
         * @return std::optional<Message> 
         */
        std::optional<Message> editReply(const adb::types::SFID &appId, const std::string &token, const SendMessageParams &params);
    private:
        InteractionsApi(const std::string &baseUrl);
    private:
        const std::string baseUrl_;
        const std::string webhooksUrl_;
    };
}