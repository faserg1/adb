#include "token-bot.hpp"
#include <cfg/secrets.hpp>
#include <fmt/core.h>
using namespace adb::api;

TokenBot::HeaderRow TokenBot::getBotAuthTokenHeader()
{
    auto value = fmt::format("Bot {}", adb::cfg::Secrets::GetBotToken());
    return {"Authorization", value};
}