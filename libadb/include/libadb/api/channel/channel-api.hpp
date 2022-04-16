#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>
#include <vector>

#include <libadb/api/channel/data/get-messages.hpp>
#include <libadb/api/channel/data/followed-channel.hpp>
#include <libadb/api/message/data/create-message.hpp>
#include <libadb/api/message/data/edit-message.hpp>
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
         * @brief Get a channel by ID. If the channel is a thread, a thread member object is included in the returned result.
         * @details https://discord.com/developers/docs/resources/channel#get-channel
         * @param channelId Channel ID
         */
        LIBADB_API std::optional<Channel> getChannel(const adb::types::SFID &channelId);
        /**
         * @brief Delete a channel, or close a private message.
         * @details https://discord.com/developers/docs/resources/channel#deleteclose-channel
         * @param channelId Channel ID to delete
         * @param reason Reason of deleteting channel (for audit log)
         */
        LIBADB_API bool deleteChannel(const adb::types::SFID &channelId, std::optional<std::string> reason = {});
        /**
         * @brief Get array of messages from the channel
         * @details https://discord.com/developers/docs/resources/channel#get-channel-messages
         * @param channelId Channel, where to get messages
         * @param opt Options, where in the channel get messages
         * @param limit Limit of messages, 1-100, default: 50
         */
        LIBADB_API std::vector<Message> getMessages(adb::types::SFID channelId, std::optional<GetMessagesOpt> opt, std::optional<uint8_t> limit);
        /**
         * @brief Returns a specific message in the channel.
         * If operating on a guild channel, this endpoint requires the READ_MESSAGE_HISTORY permission to be present on the current user. 
         * @details https://discord.com/developers/docs/resources/channel#get-channel-message
         * @param channelId Channel ID
         * @param messageId Message ID
         */
        LIBADB_API std::optional<Message> getMessage(const adb::types::SFID &channelId, const adb::types::SFID &messageId);
        /**
         * @brief Create a reaction for the message.
         * This endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user.
         * Additionally, if nobody else has reacted to the message using this emoji,
         * this endpoint requires the 'ADD_REACTIONS' permission to be present on the current user.
         * 
         * @details https://discord.com/developers/docs/resources/channel#create-reaction
         * @param channelId The ID of the channel, where the message exists.
         * @param messageId The ID of the message, to add reaction.
         * @param emoji Unicode emoji. To use custom emoji, you must encode it in the format name:id with the emoji name and emoji id. 
         */
        LIBADB_API bool createReaction(adb::types::SFID channelId, adb::types::SFID messageId, std::string emoji);
        /**
         * @brief Post a message to a guild text or DM channel.
         * @details https://discord.com/developers/docs/resources/channel#create-message
         * @param channelId Channel, where to create messages
         * @param params Message Create Params
         * @return If success, returns a message object.
         */
        LIBADB_API std::optional<Message> createMessage(adb::types::SFID channelId, const CreateMessageParams &params);
        /**
         * @brief Edit a previously sent message.
         * @details https://discord.com/developers/docs/resources/channel#edit-message
         * @param channelId Channel, where to edit messages
         * @param messageId Message ID to edit
         * @param params Message Edit Params
         * @return If success, returns a message object. 
         */
        LIBADB_API std::optional<Message> editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const EditMessageParams &params);
        /**
         * @brief Delete a message.
         * If operating on a guild channel and trying to delete a message that was not sent by the current user,
         * this endpoint requires the MANAGE_MESSAGES permission.
         * @details https://discord.com/developers/docs/resources/channel#delete-message
         * @param channelId Channel, where to delete messages
         * @param messageId Messages ID to delete
         * @param reason Reason of deleteting message (for audit log)
         */
        LIBADB_API bool deleteMessage(const adb::types::SFID &channelId, const adb::types::SFID &messageId, std::optional<std::string> reason = {});
        /**
         * @brief Bulk Delete messages from channel, not elder than 14 days
         * @details https://discord.com/developers/docs/resources/channel#bulk-delete-messages
         * @param channelId Channel, where to delete messages
         * @param messageIds Messages IDs, that should be deleted (2-100)
         * @param reason Reason of deleteting messages (for audit log)
         */
        LIBADB_API bool bulkDeleteMessages(adb::types::SFID channelId, std::vector<adb::types::SFID> messageIds, std::optional<std::string> reason = {});
        /**
         * @brief Follow a News Channel to send messages to a target channel.
         * @details https://discord.com/developers/docs/resources/channel#follow-news-channel
         * @param channelId Channel ID
         * @param webhookChannelId ID of target channel
         */
        LIBADB_API std::optional<FollowedChannel> followNewsChannel(adb::types::SFID channelId, adb::types::SFID webhookChannelId);
        /**
         * @brief Returns all pinned messages in the channel
         * @details https://discord.com/developers/docs/resources/channel#get-pinned-messages
         * @param channelId Channel ID
         */
        LIBADB_API std::vector<Message> getPinnedMessages(const adb::types::SFID &channelId);
        /**
         * @brief Pin a message in a channel. 
         * @details https://discord.com/developers/docs/resources/channel#pin-message
         * @param channelId Channel ID
         * @param messageId Message ID to pin
         * @param reason reason (for audit log)
         */
        LIBADB_API bool pinMessage(const adb::types::SFID &channelId, const adb::types::SFID &messageId, std::optional<std::string> reason = {});
        /**
         * @brief Unpin a message in a channel. 
         * @details https://discord.com/developers/docs/resources/channel#unpin-message
         * @param channelId Channel ID
         * @param messageId Message ID to unpin
         * @param reason reason (for audit log)
         */
        LIBADB_API bool unpinMessage(const adb::types::SFID &channelId, const adb::types::SFID &messageId, std::optional<std::string> reason = {});
    private:
        ChannelApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}