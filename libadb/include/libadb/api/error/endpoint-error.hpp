#pragma once

#include <stdexcept>
#include <libadb/api/error/data/error.hpp>

namespace adb::api
{
    class EndpointError : public std::runtime_error
    {
    public:
        LIBADB_API EndpointError(const adb::api::Error &error);

        LIBADB_API const adb::api::Error &getError() const;
    private:
        const adb::api::Error error_;
    };
}