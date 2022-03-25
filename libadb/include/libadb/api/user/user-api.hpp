#pragma once

#include <string>
#include <libadb/api/user/data/user.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;
    class UserApi
    {
        friend DiscordApi;
    public:
        LIBADB_API User getCurrentUser();
        LIBADB_API User getUser(const adb::types::SFID id);

    private:
        UserApi(const std::string &baseUrl);

    private:
        std::string baseUrl_;
    }; 
}
