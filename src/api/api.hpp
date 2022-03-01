#pragma once

#include <string>
#include <memory>

namespace adb::api
{
    class Auth;
    class Gateway;
    class ChannelApi;
    class GuildApi;
    class InteractionsApi;


    class DiscordApi final
    {
    public:
        DiscordApi();

        std::unique_ptr<Auth> CreateAuth();
        std::unique_ptr<Gateway> CreateGateway();
        std::unique_ptr<ChannelApi> CreateChannelApi();
        std::unique_ptr<GuildApi> CreateGuildApi();
        std::unique_ptr<InteractionsApi> CreateInteractionsApi();
    private:
        const std::string baseUrl_;
    };
}