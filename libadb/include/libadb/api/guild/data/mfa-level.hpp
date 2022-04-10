#pragma once

namespace adb::api
{
    /**
     * @brief MFA Level
     * @details https://discord.com/developers/docs/resources/guild#guild-object-mfa-level
     */
    enum class MFALevel
    {
        /// guild has no MFA/2FA requirement for moderation actions
        NONE = 0,
        /// guild has a 2FA requirement for moderation actions
        ELEVATED = 1,
    };
}