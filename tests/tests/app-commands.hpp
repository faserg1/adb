#pragma once

#include <memory>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void checkAppCommands(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);
void checkAppCommands2(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);
void checkAppCommands3(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);