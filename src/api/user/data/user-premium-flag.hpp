#pragma once

namespace adb::api
{
    /**
     * @brief Premium Types
     * @details https://discord.com/developers/docs/resources/user#user-object-premium-types
     */
    enum class UserPremiumType : uint8_t
    {
        None = 0,
        NitroClassic = 1,
        Nitro = 2,
    };
}