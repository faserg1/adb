#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>

using namespace adb::api;
using namespace adb::types;

struct GatewayEvents::Subscribers
{
    struct EventSubscriber
    {
        size_t lastInternalId = 0;
        std::unordered_map<size_t, GatewayEvents::Subscriber> subscribers;
    };
    std::unordered_map<Event, EventSubscriber> eventSubscribers;
};

class GatewayEvents::GatewaySubscription : public Subscription
{
public:
    ~GatewaySubscription()
    {
        auto eventSub = subscribers_.eventSubscribers.find(event_);
        if (eventSub == subscribers_.eventSubscribers.end())
            return;
        auto it = eventSub->second.subscribers.find(internalId_);
        if (it == eventSub->second.subscribers.end())
            return;
        eventSub->second.subscribers.erase(it);
    }
    GatewaySubscription(GatewayEvents::Subscribers &subs, Event ev, size_t internalId) :
        subscribers_(subs), event_(ev), internalId_(internalId)
    {
    }
private:
    GatewayEvents::Subscribers &subscribers_;
    const Event event_;
    const size_t internalId_;
};

GatewayEvents::GatewayEvents() : subs_(std::make_unique<Subscribers>())
{

}

GatewayEvents::~GatewayEvents()
{

}

std::shared_ptr<GatewayEvents> GatewayEvents::create()
{
    return std::shared_ptr<GatewayEvents>(new GatewayEvents(), [](auto *ptr){delete ptr;});
}

std::unique_ptr<Subscription> GatewayEvents::subscribe(Event ev, Subscriber sub)
{
    auto it = subs_->eventSubscribers.find(ev);
    if (it == subs_->eventSubscribers.end())
    {
        subs_->eventSubscribers.insert({ev, GatewayEvents::Subscribers::EventSubscriber{}});
        it = subs_->eventSubscribers.find(ev);
    }
    auto id = it->second.lastInternalId++;
    it->second.subscribers.insert({id, sub});
    return std::make_unique<GatewaySubscription>(*subs_, ev, id);
}

std::future<nlohmann::json> GatewayEvents::waitOne(Event ev)
{
    return std::async(std::launch::async, [this, ev]() -> nlohmann::json
    {
        auto promise = std::make_shared<std::promise<nlohmann::json>>();
        auto future = promise->get_future();
        auto sub = subscribe(ev, [promise = std::move(promise)](auto ev, auto data)
        {
            promise->set_value(data);
        });
        return future.get();
    });
}

void GatewayEvents::onDispatch(const Dispatch &dispatch)
{
    auto eventSub = subs_->eventSubscribers.find(dispatch.event);
    if (eventSub == subs_->eventSubscribers.end())
        return;
    for (const auto &sub : eventSub->second.subscribers)
        sub.second(dispatch.event, dispatch.data);
}