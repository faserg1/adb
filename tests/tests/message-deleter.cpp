#include "message-deleter.hpp"
#include <libadb/api/api.hpp>
#include <vector>
#include <libadb/api/channel/channel-api.hpp>

using namespace adb::api;
using namespace adb::types;

void deleteMessagesFrom(DiscordApi &api, SFID channelId, SFID idFrom)
{
    
    auto channelApi = api.CreateChannelApi();
    auto opt = GetMessagesOpt
    {
        .type = GetMessagesOptType::After,
        .messageId = idFrom
    };
    do 
    {
        std::vector<SFID> toDelete;
        auto messages = channelApi->getMessages(channelId, opt, 100);
        for (auto &message : messages)
        {
            toDelete.push_back(message.id);
        }
        opt.messageId = messages.back().id;
        channelApi->bulkDeleteMessages(channelId, toDelete, "Fuck that shit!");
        if (messages.empty() || messages.size() < 100)
            break;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5000ms);
    } while (true);
    int i = 0;
}