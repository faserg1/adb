#include "test-rate.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/channel/channel-api.hpp>
using namespace adb::api;
using namespace adb::types;

void checkRate(DiscordApi &api, std::shared_ptr<Gateway> gateway)
{
    auto channelApi = api.CreateChannelApi();
    auto channel = channelApi->getMessage(SFID{"918981635918159946"}, SFID{"966046237147140136"});
}