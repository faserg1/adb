#pragma once

#include <memory>

namespace adb::api
{
    class GatewayEvents;
    class Context;

    class Interactions
    {
    public:
        Interactions(std::shared_ptr<GatewayEvents> events);
        
    private:
        std::shared_ptr<GatewayEvents> events_;
    };
}
