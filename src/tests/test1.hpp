#pragma once

#include <memory>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void checkSmth(adb::api::DiscordApi &api, adb::api::Gateway &gateway);