#pragma once

#include <memory>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void checkUser(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);