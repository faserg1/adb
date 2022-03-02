#pragma once

#include <types/snowflake.hpp>
#include <string>
#include <api/message/data/send-message.hpp>

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
    private:
        InteractionsApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}