#pragma once

#include <string>
#include <memory>

#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/cfg/secrets.hpp>


namespace adb::api
{
    class Context;
    class Auth;
    class Gateway;
    class MediaGateway;
    class ChannelApi;
    class GuildApi;
    class InteractionsApi;
    class UserApi;
    class StickerApi;


    class DiscordApi final
    {
    public:
        LIBADB_API DiscordApi(const adb::cfg::SecretsData &secrets, uint8_t version = 9);

        LIBADB_API std::unique_ptr<Auth> CreateAuth();
        LIBADB_API std::shared_ptr<Gateway> GetGateway();
        LIBADB_API std::unique_ptr<MediaGateway> GetMediaGateway(adb::types::SFID guildId);
        LIBADB_API std::unique_ptr<ChannelApi> CreateChannelApi();
        LIBADB_API std::unique_ptr<GuildApi> CreateGuildApi();
        LIBADB_API std::unique_ptr<InteractionsApi> CreateInteractionsApi();
        LIBADB_API std::unique_ptr<UserApi> CreateUserApi();
        LIBADB_API std::unique_ptr<StickerApi> CreateStickerApi();
    private:
        std::shared_ptr<Gateway> gatewayInstance_;
        std::shared_ptr<Context> context_;
    };
}