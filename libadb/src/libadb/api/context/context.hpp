#pragma once

#include <memory>
#include <string>

namespace adb::api
{
    class Context : public std::enable_shared_from_this<Context>
    {
    public:
        Context(const std::string &baseUrl);

        const std::string getBaseUrl() const;
    private:
        const std::string baseUrl_;
    };
}