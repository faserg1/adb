#pragma once

#include <string>
#include <libadb/api/user/data/user.hpp>

namespace adb::api
{
    class DiscordApi;
    class UserApi
    {
        friend DiscordApi;
    public:
        User getCurrentUser();

    private:
        UserApi(const std::string &baseUrl);

    private:
        std::string baseUrl_;
    }; 
}
