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
}