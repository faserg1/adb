#pragma once

#include <memory>
#include <libadb/types/subscription.hpp>
#include <libadb/types/snowflake.hpp>
#include <optional>
#include <future>
#include <thread>

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

    void receiveWorker(std::stop_token stop);
private:
    adb::api::DiscordApi &api_;
    std::shared_ptr<adb::api::Gateway> gateway_;
    std::shared_ptr<adb::api::VoiceGateway> voiceGateway_;
    std::unique_ptr<adb::api::ChannelApi> channelApi_;
    std::vector<std::unique_ptr<adb::types::Subscription>> subs_;
    std::jthread voiceDataThreadReceiver;

    bool onConnected_ = false;
};