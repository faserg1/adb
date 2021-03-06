#pragma once

#include <optional>
#include <string>
#include <libadb/types/snowflake.hpp>
#include <libadb/types/color.hpp>
#include <libadb/types/nullable.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/api/user/data/user-flags.hpp>
#include <libadb/api/user/data/user-premium-flag.hpp>
#include <libadb/libadb.hpp>
#include <libadb/resource/image.hpp>
#include <libadb/resource/locale.hpp>

namespace adb::api
{
    /**
     * @brief User Object
     * @details https://discord.com/developers/docs/resources/user#user-object
     */
    struct User
    {
        /// the user's id
        adb::types::SFID id;
        /// the user's username, not unique across the platform
        std::string username;
        /// the user's 4-digit discord-tag
        std::string discriminator;
        /// the user's avatar hash
        adb::types::Nullable<adb::resource::Image> avatar;
        /// whether the user belongs to an OAuth2 application
        std::optional<bool> bot;
        /// whether the user is an Official Discord System user (part of the urgent message system)
        std::optional<bool> system;
        /// whether the user has two factor enabled on their account
        std::optional<bool> mfaEnabled;
        /// the user's banner hash
        std::optional<adb::types::Nullable<adb::resource::Image>> banner;
        /// the user's banner color encoded as an integer representation of hexadecimal color code
        std::optional<adb::types::Color> accentColor;
        /// the user's chosen language option
        std::optional<adb::resource::Locale> locale;
        /// whether the email on this account has been verified
        std::optional<bool> verified;
        /// the user's email
        std::optional<std::string> email;
        /// the flags on a user's account
        std::optional<UserFlags> flags;
        /// the type of Nitro subscription on a user's account
        std::optional<UserPremiumType> premiumType;
        /// the public flags on a user's account
        std::optional<UserFlags> publicFlags;
    };

    LIBADB_API void to_json(nlohmann::json& j, const User& user);
    LIBADB_API void from_json(const nlohmann::json& j, User& user);
}