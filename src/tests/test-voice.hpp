#pragma once

#include <memory>
#include <types/subscription.hpp>
#include <types/snowflake.hpp>
#include <optional>
#include <future>

namespace adb::api
{
    class DiscordApi;
    class ChannelApi;
    class Gateway;
    class VoiceGateway;
}

class TestVoice
{
public:
    TestVoice(adb::api::DiscordApi &api, std::shared_ptr<adb::api::Gateway> gateway);
    ~TestVoice();
private:
    void init();
    void onMessageChoose(adb::types::SFID channelId);
    std::future<bool> onMessageConnect(adb::types::SFID channelId);
    void onDisconnect();
private:
    adb::api::DiscordApi &api_;
    std::shared_ptr<adb::api::Gateway> gateway_;
    std::shared_ptr<adb::api::VoiceGateway> voiceGateway_;
    std::unique_ptr<adb::api::ChannelApi> channelApi_;
    std::vector<std::unique_ptr<adb::types::Subscription>> subs_;

    bool onConnected_ = false;
};