#include "secrets.hpp"
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

adb::cfg::SecretsData Secrets::data_ = {
    .appId = ADB_APP_ID,
    .publicKey = ADB_PUBLIC_KEY,
    .clientId = ADB_CLIENT_ID,
    .clientSecret = ADB_CLIENT_SECRET,
    .botToken = ADB_BOT_TOKEN
};
