#pragma once

#include <libadb/types/snowflake.hpp>
#include <string>
#include <optional>

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
        LIBADB_API bool createReaction(adb::types::SFID channelId, adb::types::SFID messageId, std::string emoji);
        LIBADB_API std::optional<Message> sendMessage(adb::types::SFID channelId, const SendMessageParams &params);
        LIBADB_API std::optional<Message> editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const SendMessageParams &params);
    private:
        ChannelApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}