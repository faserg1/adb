#pragma once

#include <types/snowflake.hpp>
#include <string>
#include <optional>

#include <api/message/data/send-message.hpp>
#include <api/message/data/message.hpp>

namespace adb::api
{
    class DiscordApi;

    class ChannelApi
    {
        friend DiscordApi;
    public:
        bool createReaction(adb::types::SFID channelId, adb::types::SFID messageId, std::string emoji);
        std::optional<Message> sendMessage(adb::types::SFID channelId, const SendMessageParams &params);
        std::optional<Message> editMessage(adb::types::SFID channelId, adb::types::SFID messageId, const SendMessageParams &params);
    private:
        ChannelApi(const std::string &baseUrl);
    private:
        std::string baseUrl_;
    };
}