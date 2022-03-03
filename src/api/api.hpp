#pragma once

#include <string>
#include <memory>

#include <types/snowflake.hpp>
namespace adb::api
{
    class Auth;
    class Gateway;
    class VoiceGateway;
    class ChannelApi;
    class GuildApi;
    class InteractionsApi;
    class UserApi;


    class DiscordApi final
    {
    public:
        DiscordApi(uint8_t version = 9);

        std::unique_ptr<Auth> CreateAuth();
        std::shared_ptr<Gateway> GetGateway();
        std::unique_ptr<VoiceGateway> GetVoiceGateway(adb::types::SFID guildId);
        std::unique_ptr<ChannelApi> CreateChannelApi();
        std::unique_ptr<GuildApi> CreateGuildApi();
        std::unique_ptr<InteractionsApi> CreateInteractionsApi();
        std::unique_ptr<UserApi> CreateUserApi();
    private:
        const std::string baseUrl_;
        std::shared_ptr<Gateway> gatewayInstance_;
    };
}