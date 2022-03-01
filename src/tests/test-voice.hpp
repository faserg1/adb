#pragma once

#include <memory>
#include <types/subscription.hpp>
#include <types/snowflake.hpp>
#include <optional>

namespace adb::api
{
    class DiscordApi;
    class ChannelApi;
    class Gateway;
}

class TestVoice
{
public:
    TestVoice(adb::api::DiscordApi &api, adb::api::Gateway &gateway);
    ~TestVoice();
private:
    void init();
    void onMessageChoose(adb::types::SFID channelId);
    void onMessageConnect(adb::types::SFID channelId);
private:
    adb::api::DiscordApi &api_;
    adb::api::Gateway &gateway_;
    std::unique_ptr<adb::api::ChannelApi> channelApi_;
    std::vector<std::unique_ptr<adb::types::Subscription>> subs_;

    bool onConnected_ = false;
};