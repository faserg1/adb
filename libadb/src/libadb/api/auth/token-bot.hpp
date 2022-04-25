#pragma once

#include <utility>
#include <string>
#include <memory>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class Context;

    class TokenBot final
    {
    public:
        using HeaderRow = std::pair<std::string, std::string>;
        LIBADB_API static HeaderRow getBotAuthTokenHeader(std::shared_ptr<const Context> context);
    };
    
}