#pragma once

#include <cstdint>
#include <string>
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

        static adb::types::SFID GetAppId();
        static std::string_view GetPublicKey();
        static adb::types::SFID GetClientId();
        static std::string_view GetClientSecret();
        static std::string_view GetBotToken();

        static void OverrideSecrets(const SecretsData& data);
    private:
        static SecretsData data_;
    };
}