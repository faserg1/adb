#include <libadb/cfg/secrets.hpp>
using namespace adb::cfg;

#ifndef ADB_APP_ID
#define ADB_APP_ID 0
#endif

#ifndef ADB_PUBLIC_KEY
#define ADB_PUBLIC_KEY ""
#endif

#ifndef ADB_CLIENT_ID
#define ADB_CLIENT_ID 0
#endif

#ifndef ADB_CLIENT_SECRET
#define ADB_CLIENT_SECRET ""
#endif

#ifndef ADB_BOT_TOKEN
#define ADB_BOT_TOKEN ""
#endif

SecretsData Secrets::data_ = {
    .appId = ADB_APP_ID,
    .publicKey = ADB_PUBLIC_KEY,
    .clientId = ADB_CLIENT_ID,
    .clientSecret = ADB_CLIENT_SECRET,
    .botToken = ADB_BOT_TOKEN
};

adb::types::SFID Secrets::GetAppId()
{
    return data_.appId;
}

std::string_view Secrets::GetPublicKey()
{
    return data_.publicKey;
}

adb::types::SFID Secrets::GetClientId()
{
    return data_.clientId;
}

std::string_view Secrets::GetClientSecret()
{
    return data_.clientSecret;
}

std::string_view Secrets::GetBotToken()
{
    return data_.botToken;
}

void Secrets::OverrideSecrets(const SecretsData& data)
{
    data_ = data;
}