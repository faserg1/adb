#pragma once

#include <utility>
#include <string>
#include <libadb/libadb.hpp>

namespace adb::api
{
    class TokenBot final
    {
    public:
        using HeaderRow = std::pair<std::string, std::string>;
        LIBADB_API static HeaderRow getBotAuthTokenHeader();
    };
    
}