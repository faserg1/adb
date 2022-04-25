#include <libadb/api/auth/token-bot.hpp>
#include <libadb/cfg/secrets.hpp>
#include <libadb/api/context/context.hpp>
#include <fmt/core.h>
using namespace adb::api;

TokenBot::HeaderRow TokenBot::getBotAuthTokenHeader(std::shared_ptr<const Context> context)
{
    auto value = fmt::format("Bot {}", context->getSecrets().botToken);
    return {"Authorization", value};
}