#pragma once

#include <cpr/cpr.h>
#include <optional>
#include <string>
#include <libadb/api/rate/data/rate-limit.hpp>

namespace adb::api
{
    bool hasRateLimit(const cpr::Header &header);
    RateLimit readRate(const cpr::Header &header);
}