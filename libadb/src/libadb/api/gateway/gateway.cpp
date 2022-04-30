#include <libadb/api/gateway/gateway.hpp>
#include <libadb/api/gateway/gateway-events.hpp>
#include <libadb/api/gateway/gateway-controller.hpp>
#include <libadb/api/context/context.hpp>
#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/api/gateway/data/identity.hpp>
#include <libadb/api/gateway/data/hello.hpp>
#include <libadb/api/gateway/data/dispatch.hpp>
#include <libadb/cfg/secrets.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

Gateway::Gateway(std::shared_ptr<Context> context, const std::string &gatewayUrl, Intents requiredIntents) :
    context_(context),
    controller_(std::make_unique<GatewayController>(gatewayUrl, context->getSecrets().botToken, requiredIntents)),
    events_(GatewayEvents::create())
{
    controller_->setDispatchFunction([this](const auto &msg)
    {
        onMessage(msg);
    });
}

Gateway::~Gateway()
{
    stop();
}

void Gateway::start()
{
    return controller_->start();
}

void Gateway::stop()
{
    controller_->stop();
}

void Gateway::runUnlessStopped()
{
    controller_->runUnlessStopped();
}

bool Gateway::send(const Payload &msg)
{
    return controller_->send(msg);
}

Intents Gateway::getIntents()
{
    return controller_->getIntents();
}

std::shared_ptr<GatewayEvents> Gateway::events() const
{
    return events_;
}

void Gateway::onMessage(const Payload &msg)
{
    switch (msg.op)
    {
        case GatewayOpCode::Dispatch:
        {
            auto eventType = from_string(msg.eventName.value());
            if (eventType != Event::UNKNOWN)
            {
                onDispatch({
                    .event = eventType,
                    .data = msg.data
                });
            }
            else
            {
                onDispatchUnknown(msg.eventName.value(), msg.data);
            }
            break;
        }
    }
}

void Gateway::onDispatch(const Dispatch &dispatch)
{
    events_->onDispatch(dispatch);
}

void Gateway::onDispatchUnknown(const std::string &eventName, const nlohmann::json &data)
{
    // TODO: 
}