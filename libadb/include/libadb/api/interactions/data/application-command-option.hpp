#pragma once

#include <string>
#include <optional>
#include <vector>
#include <variant>
#include <nlohmann/json_fwd.hpp>

#include <libadb/libadb.hpp>
#include <libadb/resource/localization-map.hpp>
#include <libadb/api/interactions/data/application-command-option-type.hpp>
#include <libadb/api/interactions/data/application-command-option-choice.hpp>
#include <libadb/api/channel/data/channel-type.hpp>
#include <libadb/types/nullable.hpp>

namespace adb::api
{
    /**
     * @brief Application Command Options
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure
     */
    struct ApplicationCommandOption
    {
        /// the type of option
        ApplicationCommandOptionType type;
        /// 1-32 character name
        std::string name;
        /// Localization dictionary for the name field. Values follow the same restrictions as name
        std::optional<adb::types::Nullable<adb::resource::LocalizationMap>> nameLocalizations;
        /// 1-100 character description
        std::string description;
        /// Localization dictionary for the description field. Values follow the same restrictions as description
        std::optional<adb::types::Nullable<adb::resource::LocalizationMap>> descriptionLocalizations;
        /// if the parameter is required or optional (default false)
        /// @note if true, this command option must be listed before command optionds having false
        std::optional<bool> required;
        /// choices for STRING, INTEGER, and NUMBER types for the user to pick from, max 25
        std::optional<std::vector<ApplicationCommandOptionChoice>> choices;
        /// if the option is a subcommand or subcommand group type, these nested options will be the parameters
        std::optional<std::vector<ApplicationCommandOption>> options;
        /// if the option is a channel type, the channels shown will be restricted to these types
        std::optional<std::vector<ChannelType>> channelTypes;
        /// if the option is an INTEGER or NUMBER type, the minimum value permitted
        std::optional<std::variant<int64_t, long double>> minValue;
        /// if the option is an INTEGER or NUMBER type, the maximum value permitted
        std::optional<std::variant<int64_t, long double>> maxValue;
        /// if autocomplete interactions are enabled for this STRING, INTEGER, or NUMBER type option
        std::optional<bool> autocomplete;
    };

    LIBADB_API void to_json(nlohmann::json& j, const ApplicationCommandOption& option);
    LIBADB_API void from_json(const nlohmann::json& j, ApplicationCommandOption& option);
}