#pragma once

namespace adb::api
{
    /**
     * @brief 
     * @details https://discord.com/developers/docs/resources/user#user-object-user-flags
     */
    enum class UserFlag : uint64_t
    {
        /// None
        NONE = 0,
        /// Discord Employee
        STAFF					 = (1 << 0),
        /// Partnered Server Owner
        PARTNER					 = (1 << 1),
        /// HypeSquad Events Coordinator
        HYPESQUAD				 = (1 << 2),
        /// Bug Hunter Level 1
        BUG_HUNTER_LEVEL_1		 = (1 << 3),
        /// House Bravery Member
        HYPESQUAD_ONLINE_HOUSE_1 = (1 << 6),
        /// House Brilliance Member
        HYPESQUAD_ONLINE_HOUSE_2 = (1 << 7),
        /// House Balance Member
        HYPESQUAD_ONLINE_HOUSE_3 = (1 << 8),
        /// Early Nitro Supporter
        PREMIUM_EARLY_SUPPORTER	 = (1 << 9),
        /// User is a team
        /// @details https://discord.com/developers/docs/topics/teams
        TEAM_PSEUDO_USER		 = (1 << 10),
        /// Bug Hunter Level 2
        BUG_HUNTER_LEVEL_2		 = (1 << 14),
        /// Verified Bot
        VERIFIED_BOT			 = (1 << 16),
        /// Early Verified Bot Developer
        VERIFIED_DEVELOPER		 = (1 << 17),
        /// Discord Certified Moderator
        CERTIFIED_MODERATOR		 = (1 << 18),
        /// Bot uses only HTTP interactions and is shown in the online member list
        /// @details https://discord.com/developers/docs/interactions/receiving-and-responding#receiving-an-interaction
        BOT_HTTP_INTERACTIONS	 = (1 << 19),
    };

    using UserFlags = uint64_t;

    constexpr UserFlags operator+(UserFlag p)
    {
        return static_cast<uint64_t>(p);
    }

    constexpr UserFlags operator|(UserFlag p1, UserFlag p2)
    {
        return static_cast<uint64_t>(p1) | static_cast<uint64_t>(p2);
    }

    constexpr UserFlags operator|(UserFlags p1, UserFlag p2)
    {
        return p1 | static_cast<uint64_t>(p2);
    }
}