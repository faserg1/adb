#pragma once

#include <utility>
#include <string>

namespace adb::api
{
    class TokenBot final
    {
    public:
        using HeaderRow = std::pair<std::string, std::string>;
        static HeaderRow getBotAuthTokenHeader();
    };
    
}