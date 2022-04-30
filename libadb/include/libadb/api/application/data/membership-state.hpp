#pragma once

namespace adb::api
{
    /**
     * @brief Team Membership State
     * @details https://discord.com/developers/docs/topics/teams#data-models-membership-state-enum
     */
    enum class MembershipState
    {
        INVITED = 1,
        ACCEPTED = 2
    };
}