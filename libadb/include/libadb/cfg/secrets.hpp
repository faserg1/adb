#pragma once

#include <cstdint>
#include <string>
#include <libadb/libadb.hpp>
#include <libadb/types/snowflake.hpp>

namespace adb::cfg
{
    struct SecretsData
    {
        adb::types::SFID appId;
        std::string publicKey;
        adb::types::SFID clientId;
        std::string clientSecret;
        std::string botToken;
    };

    class Secrets final
    {
    public:
        Secrets() = delete;

        LIBADB_API static adb::types::SFID GetAppId();
        LIBADB_API static std::string_view GetPublicKey();
        LIBADB_API static adb::types::SFID GetClientId();
        LIBADB_API static std::string_view GetClientSecret();
        LIBADB_API static std::string_view GetBotToken();

        LIBADB_API static void OverrideSecrets(const SecretsData& data);
    private:
        static SecretsData data_;
    };
}