#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <future>
#include <thread>
#include <string>
#include <cstdint>

#include <libadb/api/media/data/ip-discovery.hpp>

namespace adb::api
{
    class GatewayMediaData
    {
        
    public:
        GatewayMediaData();

        void relocate(std::string ip, uint16_t port, uint32_t ssrc);
        bool start();
        std::future<void> stop();

        std::future<IPDiscovery> ipDiscovery();

        std::future<bool> sendData(const std::byte *ptr, size_t size);
        std::future<size_t> receiveData(std::byte *ptr, size_t bufferSize);

        std::future<bool> sendData(const std::vector<std::byte> &data)
        {
            return sendData(data.data(), data.size());
        }

        template <size_t Size>
        std::future<bool> sendData(const std::array<std::byte, Size> &data)
        {
            return sendData(data.data(), Size);
        }

        std::future<std::vector<std::byte>> receiveData();
    protected:
        virtual void onDataFlowStarted();
        virtual void onDataFlowStopped();

    private:
        void init();
        void socketWorker(std::stop_token stop);

    private:
        boost::asio::io_service ioService_;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint endpoint_;

        std::jthread workerThread_;

        std::string ip_;
        uint16_t port_ = {};
        uint32_t ssrc_ = {};

        size_t bufferSize_ = 4096;
    };
}