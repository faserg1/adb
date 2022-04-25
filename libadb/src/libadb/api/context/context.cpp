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

const adb::cfg::SecretsData &Context::getSecrets() const
{
    return secrets_;
}

void Context::overrideSecrets(const adb::cfg::SecretsData &data)
{
    secrets_ = data;
}