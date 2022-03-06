#pragma once

#include <string>
#include <optional>
#include <libadb/api/permissions/permissions.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class DiscordApi;

    class Auth final
    {
        friend DiscordApi; 
    public:
        LIBADB_API std::string getBotAuthUrl(Permissions permissions = 0, std::optional<adb::types::SFID> guildId = std::nullopt, bool disableGuildSelect = false);
    private:
        Auth(std::string_view baseUrl);
    private:
        const std::string authUrl_;
        const std::string tokenUrl_;
        const std::string revokeUrl_;
    };
}