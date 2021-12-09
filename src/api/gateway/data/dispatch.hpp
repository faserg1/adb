#pragma once

#include "event.hpp"
#include <nlohmann/json.hpp>

namespace adb::api
{
    struct Dispatch
    {
        Event event;
        nlohmann::json data;
    };
}