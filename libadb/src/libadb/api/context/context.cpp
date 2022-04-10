#include <libadb/api/context/context.hpp>
using namespace adb::api;

Context::Context(const std::string &baseUrl) :
    baseUrl_(baseUrl)
{
}

const std::string Context::getBaseUrl() const
{
    return baseUrl_;
}