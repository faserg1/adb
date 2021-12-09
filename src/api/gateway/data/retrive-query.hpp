#pragma once

#include <optional>
#include <string>
#include <cstdint>

namespace adb::api
{
    enum class GatewayEncoding
    {
        JSON,
        ETF
    };

    enum class GatewayCompress
    {
        ZLIB_STREAM
    };

    /**
     * @brief Gateway URL Query String Params
     * @details https://discord.com/developers/docs/topics/gateway#connecting-gateway-url-query-string-params
     */
    struct GatewayRetriveQuery
    {
        /**
         * @brief Gateway Version
         * @details https://discord.com/developers/docs/topics/gateway#gateways-gateway-versions
         */
        uint8_t version;
        /// Encoding
        GatewayEncoding encoding;
        /// NOT YET IMPLEMENTED
        std::optional<GatewayCompress> compress;
    };
}