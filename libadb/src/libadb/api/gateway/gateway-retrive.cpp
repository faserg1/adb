#include <libadb/api/gateway/gateway-retrive.hpp>
#include <libadb/api/auth/token-bot.hpp>
#include <stdexcept>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
using namespace adb::api;

GatewayRetrive::GatewayRetrive(const std::string &baseUrl) :
    baseGatewayUrl_(baseUrl + "/gateway")
{
    
}

GatewayBotRetriveData GatewayRetrive::retriveBotGateway(std::optional<GatewayRetriveQuery> queryOpt)
{
    auto requestUrl = fmt::format("{}/bot", baseGatewayUrl_);
    auto response = cpr::Get(cpr::Url{requestUrl}, cpr::Header{TokenBot::getBotAuthTokenHeader()});
    if (response.status_code < 200 || response.status_code >= 300)
    {
        throw std::runtime_error(response.status_line);
        return {};
    }
    
    auto json = nlohmann::json::parse(response.text);
    auto sessionStartLimit = json["session_start_limit"];
    auto baseUrl = json["url"].get<std::string>();
    auto gatewayUrl = baseUrl;
    if (gatewayUrl.back() != '/')
        gatewayUrl += "/";

    if (queryOpt.has_value())
    {
        auto query = queryOpt.value();
        std::vector<std::string> queryParams;
        queryParams.emplace_back(fmt::format("v={}", query.version));

        std::string encoding;
        switch (query.encoding)
        {
            case GatewayEncoding::JSON:
                encoding = "json";
                break;
            case GatewayEncoding::ETF:
                encoding = "etf";
                break;
        }

        queryParams.emplace_back(fmt::format("encoding={}", encoding));

        if (!queryParams.empty())
        {
            gatewayUrl += "?";
            for (const auto &queryParam : queryParams)
            {
                if (gatewayUrl.back() != '?')
                    gatewayUrl += "&";
                gatewayUrl += queryParam;
            }
        }
    }
    

    return GatewayBotRetriveData {
        .url = gatewayUrl,
        .shards = json["shards"].get<uint64_t>(),
        .sessionStartLimit = GatewayBotSessionStartLimit {
            .total = sessionStartLimit["total"].get<uint64_t>(),
            .remaining = sessionStartLimit["remaining"].get<uint64_t>(),
            .resetAfter = sessionStartLimit["reset_after"].get<uint64_t>(),
            .maxConcurrency = sessionStartLimit["max_concurrency"].get<uint64_t>(),
        }
    };
}