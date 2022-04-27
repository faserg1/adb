#pragma once

#include <memory>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void checkGuild(adb::api::DiscordApi &api);
void checkGuildChannels(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);
void checkRoleMemberAdd(adb::api::DiscordApi &api);
void checkGuildMembers(adb::api::DiscordApi &api);