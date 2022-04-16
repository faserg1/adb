#include "test-guild.hpp"
#include <libadb/api/api.hpp>
#include <libadb/api/channel/channel-api.hpp>
using namespace adb::api;

void testPins(adb::api::DiscordApi &api)
{
    auto channelId = adb::types::SFID{"964458591102853120"};
    auto messageId = adb::types::SFID{"964826080009650226"};
    auto channelApi = api.CreateChannelApi();
    channelApi->pinMessage(channelId, messageId, std::string{"Pin this!"});
    auto pinnedMessages = channelApi->getPinnedMessages(channelId);
    channelApi->unpinMessage(channelId, messageId, std::string{"Unpin this!"});
}