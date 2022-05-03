#pragma once

#include <memory>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void checkSmth(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);
void checkForErrors(adb::api::DiscordApi &api);
void checkCurrentApp(adb::api::DiscordApi &api);