#include "interactions.hpp"
using namespace adb::api;

adb::api::Interactions::Interactions(std::shared_ptr<GatewayEvents> events) :
    events_(events)
{

}