#pragma once

namespace adb::types
{
    class Subscription
    {
    public:
        virtual ~Subscription() = default;
    protected:
        Subscription() = default;
    };
}