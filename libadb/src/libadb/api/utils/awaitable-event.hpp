#pragma once

#include <memory>
#include <future>

namespace adb::api
{
    class AwaitableEvent
    {
        struct Details;
    public:
        AwaitableEvent();
        ~AwaitableEvent();

        void notify();
        void wait();
        void reset();
        std::future<void> waitAsync();

    private:
        std::unique_ptr<Details> data_;
    };
}