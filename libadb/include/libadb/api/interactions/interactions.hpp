#pragma once

#include <memory>
#include <vector>
#include <string>
#include <libadb/libadb.hpp>
#include <libadb/api/interactions/data/interaction.hpp>
#include <libadb/api/interactions/data/interaction-data.hpp>
#include <libadb/api/interactions/data/interaction-data-command-option.hpp>
#include <libadb/types/subscription.hpp>

namespace adb::api
{
    class GatewayEvents;
    class Context;

    class Interactions
    {
    public:
        using CommandSubscriber = std::function<void(
            const Interaction&,
            const InteractionDataApplicationCommand&,
            const std::optional<std::vector<InteractionDataCommandOption>>&)>;

        LIBADB_API Interactions(std::shared_ptr<GatewayEvents> events);
        
        LIBADB_API std::unique_ptr<adb::types::Subscription> subscribeToCommand(
            const std::string &cmdName, const std::vector<std::string> subCommandPath, CommandSubscriber subscriber
        );
    private:
        std::shared_ptr<GatewayEvents> events_;
    };
}
