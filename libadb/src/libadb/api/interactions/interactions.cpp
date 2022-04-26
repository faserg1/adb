#include <libadb/api/interactions/interactions.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/utils/algorithms.hpp>
#include <utility>
using namespace adb::api;

Interactions::Interactions(std::shared_ptr<GatewayEvents> events) :
    events_(events)
{

}

std::unique_ptr<adb::types::Subscription> Interactions::subscribeToCommand(const std::string &cmdName,
    const std::vector<std::string> subCommandPath, CommandSubscriber subscriber)
{
    return std::move(events_->subscribe<Interaction>(Event::INTERACTION_CREATE, [cmdName, subCommandPath, subscriber](auto ev, auto &interaction)
    {
        if (interaction.type != InteractionType::APPLICATION_COMMAND)
            return;
        if (!interaction.data.has_value())
            return;
        auto data = std::static_pointer_cast<InteractionDataApplicationCommand>(interaction.data.value());
        if (!data)
            return;
        if (data->name != cmdName)
            return;
        if (subCommandPath.empty())
        {
            subscriber(interaction, *data, data->options);
            return;
        }
        if (!data->options.has_value())
            return;
        auto *currentOptions = &data->options.value();
        InteractionDataCommandOption *currentOption = nullptr;
        auto currentSub = subCommandPath.begin();
        while (currentOptions && currentSub != subCommandPath.end())
        {
            currentOption = findByName(*currentOptions, std::string{*currentSub});
            if (!currentOption)
                break;
            currentSub++;
            currentOptions = currentOption->options.has_value() ? &currentOption->options.value() : nullptr;
        }
        if (!currentOption || currentSub != subCommandPath.end())
            return;
        subscriber(interaction, *data, currentOption->options);
    }));
}