#pragma once

#include <libadb/api/gateway/data/event.hpp>
#include <nlohmann/json.hpp>

namespace adb::api
{
    struct Dispatch
    {
        Event event;
        nlohmann::json data;
    };
}