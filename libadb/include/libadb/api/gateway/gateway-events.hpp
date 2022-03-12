#pragma once

#include <memory>
#include <functional>
#include <future>
#include <nlohmann/json.hpp>
#include <libadb/libadb.hpp>
#include <libadb/types/subscription.hpp>
#include <libadb/api/gateway/data/event.hpp>

namespace adb::api
{
    class Gateway;
    struct Dispatch;

    class GatewayEvents
    {
        friend Gateway;
        struct Subscribers;
        class GatewaySubscription;
    public:
        using Subscriber = std::function<void(Event, const nlohmann::json&)>;
        template <class Type>
        using TypedSubscriber = std::function<void(Event, const Type&)>;

        LIBADB_API [[nodiscard]] std::unique_ptr<adb::types::Subscription> subscribe(Event ev, Subscriber sub);
        LIBADB_API [[nodiscard]] std::future<nlohmann::json> waitOne(Event ev);

        template <class Type>
        [[nodiscard]] std::unique_ptr<adb::types::Subscription> subscribe(Event ev, TypedSubscriber<Type> sub)
        {
            auto innerSub = std::function(
                [sub](Event e, const nlohmann::json &data)
                {
                    return sub(e, data.get<Type>());
                }
            );
            return std::move(subscribe(ev, innerSub));
        }
        template <class Type>
        [[nodiscard]] std::future<Type> waitOne(Event ev)
        {
            return std::async(std::launch::async, [this, ev]() -> Type
            {
                return waitOne(ev).get().get<Type>();
            });
        }
    protected:
        GatewayEvents();
        ~GatewayEvents();

        static std::shared_ptr<GatewayEvents> create();
        
        void onDispatch(const Dispatch &dispatch);
    private:
        std::unique_ptr<Subscribers> subs_;
    };
}