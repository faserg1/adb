#pragma once

#include <string>
#include <libadb/libadb.hpp>

namespace adb::api
{
    enum class GuildFeature
    {
        /// guild has access to set an animated guild banner image
        ANIMATED_BANNER,
        /// guild has access to set an animated guild icon
        ANIMATED_ICON,
        /// guild has access to set a guild banner image
        BANNER,
        /// guild has access to use commerce features (i.e. create store channels)
        COMMERCE,
        /// guild can enable welcome screen, Membership Screening, stage channels and discovery, and receives community updates
        COMMUNITY,
        /// guild is able to be discovered in the directory
        DISCOVERABLE,
        /// guild is able to be featured in the directory
        FEATURABLE,
        /// guild has access to set an invite splash background
        INVITE_SPLASH,
        /// guild has enabled Membership Screening
        MEMBER_VERIFICATION_GATE_ENABLED,
        /// guild has enabled monetization
        MONETIZATION_ENABLED,
        /// guild has increased custom sticker slots
        MORE_STICKERS,
        /// guild has access to create news channels
        NEWS,
        /// guild is partnered
        PARTNERED,
        /// guild can be previewed before joining via Membership Screening or the directory
        PREVIEW_ENABLED,
        /// guild has access to create private threads
        PRIVATE_THREADS,
        /// guild is able to set role icons
        ROLE_ICONS,
        /// guild has access to the seven day archive time for threads
        SEVEN_DAY_THREAD_ARCHIVE,
        /// guild has access to the three day archive time for threads
        THREE_DAY_THREAD_ARCHIVE,
        /// guild has enabled ticketed events
        TICKETED_EVENTS_ENABLED,
        /// guild has access to set a vanity URL
        VANITY_URL,
        /// guild is verified
        VERIFIED,
        /// guild has access to set 384kbps bitrate in voice (previously VIP voice servers)
        VIP_REGIONS,
        /// guild has enabled the welcome screen
        WELCOME_SCREEN_ENABLED
    };

    LIBADB_API std::string to_string(GuildFeature e);
    LIBADB_API void from_string(const std::string &str, GuildFeature &feature);
}