#pragma once

#include <string>
#include <memory>

namespace adb::api
{
    class Auth;
    class Gateway;
    class ChannelApi;


    class DiscordApi final
    {
    public:
        DiscordApi();

        std::unique_ptr<Auth> CreateAuth();
        std::unique_ptr<Gateway> CreateGateway();
        std::unique_ptr<ChannelApi> CreateChannelApi();
    private:
        const std::string baseUrl_;
    };
}