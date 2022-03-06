#include <libadb/api/auth/token-bot.hpp>
#include <libadb/cfg/secrets.hpp>
#include <fmt/core.h>
using namespace adb::api;

TokenBot::HeaderRow TokenBot::getBotAuthTokenHeader()
{
    auto value = fmt::format("Bot {}", adb::cfg::Secrets::GetBotToken());
    return {"Authorization", value};
}