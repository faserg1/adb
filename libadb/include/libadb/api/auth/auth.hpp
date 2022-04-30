#pragma once

#include <string>
#include <optional>
#include <memory>
#include <libadb/api/permissions/permissions.hpp>
#include <libadb/api/application/data/application.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class Context;
    class DiscordApi;

    class Auth final
    {
        friend DiscordApi; 
    public:
        /**
         * @brief Get the Current Application Info object
         * @details https://discord.com/developers/docs/topics/oauth2#get-current-bot-application-information
         */
        LIBADB_API std::optional<Application> getCurrentApplicationInfo();
        LIBADB_API std::string getBotAuthUrl(Permissions permissions = 0, std::optional<adb::types::SFID> guildId = std::nullopt, bool disableGuildSelect = false);
    private:
        Auth(std::shared_ptr<Context> context);
    private:
        const std::shared_ptr<Context> context_;
        
        const std::string baseUrl_;
        const std::string authUrl_;
        const std::string tokenUrl_;
        const std::string revokeUrl_;
    };
}