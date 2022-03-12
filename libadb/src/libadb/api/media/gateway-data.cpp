#include <libadb/api/media/gateway-data.hpp>
using namespace adb::api;

GatewayMediaData::GatewayMediaData() :
    socket_(ioService_)
{

}

void GatewayMediaData::init()
{
    using namespace boost::asio::ip;
    socket_.open(udp::v4());
    socket_.bind(udp::endpoint(address{}, 0));
}

void GatewayMediaData::relocate(std::string ip, uint16_t port, uint32_t ssrc)
{
    using namespace boost::asio::ip;
    ip_ = ip;
    port_ = port;
    ssrc_ = ssrc;
    endpoint_ = udp::endpoint(address::from_string(ip), port);
}

std::future<IPDiscovery> GatewayMediaData::ipDiscovery()
{
    return std::async(std::launch::async, [this]() -> IPDiscovery
    {
        IPDiscovery discovery = {};
        discovery.type = IPDiscoveryType::Request;
        discovery.ssrc = ssrc_;

        auto ipDiscoveryFutureSend = sendData(toBytes(discovery));
        if (!ipDiscoveryFutureSend.get())
            throw std::runtime_error("Cannot send IPDiscovery");

        std::vector<std::byte> discoveryData = receiveData().get();
        if (discoveryData.empty())
            throw std::runtime_error("Cannot get data IPDiscovery");
        fromBytes(discoveryData, discovery);

        return discovery;
    });
}

std::future<bool> GatewayMediaData::sendData(const std::byte *ptr, size_t size)
{
    using namespace boost::asio::ip;
    auto promise = std::make_shared<std::promise<bool>>();
    socket_.async_send_to(boost::asio::buffer(ptr, size), endpoint_,
        [promise, size](auto error, auto writedBytes)
        {
            promise->set_value(!error && writedBytes == size);
        });
    return promise->get_future();
}

std::future<size_t> GatewayMediaData::receiveData(std::byte *ptr, size_t bufferSize)
{
    using namespace boost::asio::ip;
    auto promise = std::make_shared<std::promise<size_t>>();
    socket_.async_receive_from(boost::asio::buffer(ptr, bufferSize), endpoint_,
        [promise](auto error, auto readedBytes)
        {
            if (error)
                promise->set_exception(std::make_exception_ptr(error));
            else
                promise->set_value((size_t) readedBytes);
        });
    return promise->get_future();
}

std::future<std::vector<std::byte>> GatewayMediaData::receiveData()
{
    return std::async(std::launch::async, [this]() -> std::vector<std::byte>
    {
        std::vector<std::byte> buffer(bufferSize_);
        auto receivedSize = receiveData(buffer.data(), buffer.size()).get();
        buffer.resize(receivedSize);
        buffer.shrink_to_fit();
        return buffer;
    });
}

void GatewayMediaData::onDataFlowStarted()
{

}

void GatewayMediaData::onDataFlowStopped()
{

}

void GatewayMediaData::socketWorker(std::stop_token stop)
{
    onDataFlowStarted();
    while (!stop.stop_requested())
    {
        ioService_.run();
    }
    onDataFlowStopped();
}