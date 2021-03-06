#include <libadb/api/utils/awaitable-event.hpp>
#include <mutex>
#include <condition_variable>
using namespace adb::api;

struct AwaitableEvent::Details
{
    std::mutex m;
    std::condition_variable cv;
    bool done;
};

AwaitableEvent::AwaitableEvent() :
    data_(std::make_unique<Details>())
{

}

AwaitableEvent::~AwaitableEvent() = default;

void AwaitableEvent::notify()
{
    if (!data_)
        return;
    std::lock_guard lk(data_->m);
    data_->done = true;
    data_->cv.notify_one();
}

void AwaitableEvent::reset()
{
    if (!data_)
        return;
    std::lock_guard lk(data_->m);
    data_->done = false;
}

void AwaitableEvent::wait()
{
    if (!data_)
        return;
    std::unique_lock lk(data_->m);
    while (!data_->done) {
        data_->cv.wait(lk, [this](){return data_->done;});
    }
    data_->done = false;
    lk.unlock();
}

std::future<void> AwaitableEvent::waitAsync()
{
    return std::async(std::launch::async, [this]()
    {
        wait();
    });
}