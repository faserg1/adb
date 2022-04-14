#include <libadb/api/error/endpoint-error.hpp>
using namespace adb::api;

EndpointError::EndpointError(const Error &error) :
    std::runtime_error(error.message), error_(error)
{

}

const adb::api::Error &EndpointError::getError() const
{
    return error_;
}