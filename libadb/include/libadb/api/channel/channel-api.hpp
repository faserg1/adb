#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/get-messages.hpp>
#include <libadb/api/message/data/send-message.hpp>
#include <libadb/api/message/data/message.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;

    class ChannelApi
    {
        friend DiscordApi;
    public:
        
    public:
        /**
         * @brief Get array of messages from the channel
         * @details https://discord.com/developers/docs/resources/channel#get-channel-messages
         * @param channelId Channel, where to get messages
         * @param opt Options, where in the channel get messages
         * @param limit Limit of messages, 1-100, default: 50
         * @return 
         */
        LIBADB_API std::vector<Message> getMessages(adb::types::SFID channelId, std::optional<GetMessagesOpt> opt, std::optional<uint8_t> limit);
        LIBADB_API bool createReaction(adb::types::SFID channelId, adb::types::SFID messageId, std::string emoji);
        LIBADB_API std::optional<Message> sendMessage(adb::types::SFID channelId, const SendMessageParams &params);
        LIBADB_API std::optional<Message> editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const SendMessageParams &params);
        /**
         * @brief Bulk Delete messages from channel, not elder than 14 days
         * @details https://discord.com/developers/docs/resources/channel#bulk-delete-messages
         * @param channelId Channel, where to delete messages
         * @param messageIds Messages IDs, that should be deleted (2-100)
         * @param reason Reason of deleteting messages (for audit log)
         */
        LIBADB_API bool bulkDeleteMessages(adb::types::SFID channelId, std::vector<adb::types::SFID> messageIds, std::optional<std::string> reason = {});
    private:
        ChannelApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}