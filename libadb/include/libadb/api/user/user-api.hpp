#pragma once

#include <string>
#include <optional>
#include <libadb/api/user/data/user.hpp>
#include <libadb/api/channel/data/channel.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;
    class Context;

    class UserApi
    {
        friend DiscordApi;
    public:
        LIBADB_API std::optional<User> getCurrentUser();
        LIBADB_API std::optional<User> getUser(const adb::types::SFID id);
        /**
         * @brief Create a new DM channel with a user.
         * @details https://discord.com/developers/docs/resources/user#create-dm
         * @param recipientId the recipient to open a DM channel with 
         * @return Opened DM channel 
         */
        LIBADB_API std::optional<Channel> createDM(const adb::types::SFID recipientId);

    private:
        UserApi(std::shared_ptr<Context> context);

    private:
        const std::shared_ptr<Context> context_;
        const std::string baseUrl_;
    }; 
}
