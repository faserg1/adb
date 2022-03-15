#pragma once

#include <memory>
#include <libadb/types/snowflake.hpp>

namespace adb::api
{
    class DiscordApi;
    class Gateway;
}

void deleteMessagesFrom(adb::api::DiscordApi &api, adb::types::SFID channelId, adb::types::SFID idFrom);