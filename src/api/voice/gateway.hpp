#pragma once

#include <string>
#include <memory>
#include <functional>
#include <future>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    class Gateway;

    class VoiceGateway
    {
    public:
        static std::future<std::unique_ptr<VoiceGateway>> connect(std::shared_ptr<Gateway> gateway);
    private:
        VoiceGateway();
    private:
    };
}