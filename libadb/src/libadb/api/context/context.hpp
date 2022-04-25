#pragma once

#include <memory>
#include <string>
#include <libadb/cfg/secrets.hpp>

namespace adb::api
{
    class Context : public std::enable_shared_from_this<Context>
    {
    public:
        Context(const std::string &baseUrl);

        const std::string getBaseUrl() const;
        const adb::cfg::SecretsData &getSecrets() const;

        void overrideSecrets(const adb::cfg::SecretsData &data);
    private:
        const std::string baseUrl_;
        adb::cfg::SecretsData secrets_;
    };
}