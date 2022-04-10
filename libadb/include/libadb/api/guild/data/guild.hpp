#pragma once

#include <optional>
#include <string>
#include <vector>
#include <libadb/libadb.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/nullable.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/resource/locale.hpp>
#include <libadb/api/guild/data/verification-level.hpp>
#include <libadb/api/guild/data/default-message-notification-level.hpp>
#include <libadb/api/guild/data/explicit-content-filter-level.hpp>
#include <libadb/api/permissions/role.hpp>
#include <libadb/api/emoji/data/emoji.hpp>
#include <libadb/api/guild/data/guild-features.hpp>
#include <libadb/api/guild/data/mfa-level.hpp>
#include <libadb/api/guild/data/system-channel-flags.hpp>
#include <libadb/api/guild/data/premium-tier.hpp>
#include <libadb/api/guild/data/welcome-screen.hpp>
#include <libadb/api/guild/data/guild-nsfw-level.hpp>
#include <libadb/api/sticker/data/sticker.hpp>

namespace adb::api
{
    /**
     * @brief The Guild Object, in Discord UI known as "Server"
     * @details https://discord.com/developers/docs/resources/guild#guild-resource
     */
    struct Guild
    {
        /// guild id
        adb::types::SFID id;
        /// guild name (2-100 characters, excluding trailing and leading whitespace)
        std::string name;
        /// icon
        adb::types::Nullable<adb::resource::Image> icon;
        /// icon hash, returned when in the template object
        std::optional<adb::types::Nullable<std::string>> iconHash;
        /// splash
        adb::types::Nullable<adb::resource::Image> splash;
        /// discovery splash; only present for guilds with the "DISCOVERABLE" feature
        adb::types::Nullable<adb::resource::Image> discoverySplash;
        /// id of owner
        adb::types::SFID ownerId;
        /// id of afk channel
        adb::types::Nullable<adb::types::SFID> afkChannelId;
        /// afk timeout in seconds
        int64_t afkTimeout;
        /// true if the server widget is enabled
        std::optional<bool> widgetEnabled;
        /// the channel id that the widget will generate an invite to, or `nullptr` if set to no invite
        std::optional<adb::types::Nullable<adb::types::SFID>> widgetChannelId;
        /// verification level required for the guild
        VerificationLevel verificationLevel;
        /// default message notifications level
        DefaultMessageNotificationLevel defaultMessageNotifications;
        /// explicit content filter level
        ExplicitContentFilterLevel explicitContentFilter;
        /// roles in the guild
        std::vector<Role> roles;
        /// custom guild emojis
        std::vector<Emoji> emojis;
        /// enabled guild features
        std::vector<GuildFeature> features;
        /// application id of the guild creator if it is bot-created
        adb::types::Nullable<adb::types::SFID> applicationId;
        /// the id of the channel where guild notices such as welcome messages and boost events are posted
        adb::types::Nullable<adb::types::SFID> systemChannelId;
        /// system channel flags
        SystemChannelFlags systemChannelFlags;
        /// the id of the channel where Community guilds can display rules and/or guidelines
        adb::types::Nullable<adb::types::SFID> rulesChannelId;

        /* Some Event fields in Discord API Docs */

        /// the maximum number of presences for the guild (`nullptr` is always returned, apart from the largest of guilds)
        std::optional<adb::types::Nullable<int64_t>> maxPresences;
        /// the maximum number of members for the guild
        std::optional<int64_t> maxMembers;
        /// the vanity url code for the guild
        adb::types::Nullable<std::string> vanityUrlCode;
        /// the description of a guild
        adb::types::Nullable<std::string> description;
        /// banner
        adb::types::Nullable<adb::resource::Image> banner;
        /// premium tier (Server Boost level)
        PremiumTier premiumTier;
        /// the number of boosts this guild currently has
        std::optional<int64_t> premiumSubscriptionCount;
        /// the preferred locale of a Community guild;
        /// used in server discovery and notices from Discord, and sent in interactions;
        /// defaults to `EnglishUS`
        adb::resource::Locale preferredLocale;
        /// the id of the channel where admins and moderators of Community guilds receive notices from Discord
        adb::types::Nullable<adb::types::SFID> publicUpdateChannelId;
        /// the maximum amount of users in a video channel
        std::optional<int64_t> maxVideoChannelUsers;
        /// approximate number of members in this guild, returned from the GET /guilds/<id> endpoint when with_counts is true
        std::optional<int64_t> approximateMemberCount;
        /// approximate number of non-offline members in this guild, returned from the GET /guilds/<id> endpoint when with_counts is true
        std::optional<int64_t> approximatePresenceCount;
        /// the welcome screen of a Community guild, shown to new members, returned in an Invite's guild object
        std::optional<WelcomeScreen> welcomeScreen;
        /// guild NSFW level
        GuildNSFWLevel nsfwLevel;

        /* Some Event fields in Discord API Docs */

        /// custom guild stickers
        std::optional<std::vector<Sticker>> stickers;

        /* Some Event fields in Discord API Docs */

        /// whether the guild has the boost progress bar enabled
        bool premiumProgressBarEnabled;
    };

    /**
     * @brief Same as Guild, but relative to current user
     */
    struct GuildRelative : Guild
    {

    };

    LIBADB_API void to_json(nlohmann::json& j, const Guild& guild);
    LIBADB_API void from_json(const nlohmann::json& j, Guild& guild);

    LIBADB_API void to_json(nlohmann::json& j, const GuildRelative& guild);
    LIBADB_API void from_json(const nlohmann::json& j, GuildRelative& guild);
}