#pragma once

#include <cpr/cpr.h>
#include <optional>
#include <string>

namespace adb::api
{
    void fillReason(cpr::Header &header, std::optional<std::string> reason);
}