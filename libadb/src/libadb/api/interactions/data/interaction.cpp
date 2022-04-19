#include <libadb/api/interactions/data/interaction.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Interaction& interaction)
{
    // todo: 
}

void adb::api::from_json(const nlohmann::json& j, Interaction& interaction)
{
    j.at("id").get_to(interaction.id);
    j.at("application_id").get_to(interaction.applicationId);
    j.at("type").get_to(interaction.type);
    if (interaction.type == InteractionType::MESSAGE_COMPONENT)
    {
        auto data = std::make_shared<InteractionDataComponent>();
        j.at("data").get_to(*data);
        interaction.data = data;
    }
    else if (interaction.type == InteractionType::APPLICATION_COMMAND ||
            interaction.type == InteractionType::APPLICATION_COMMAND_AUTOCOMPLETE)
    {
        auto data = std::make_shared<InteractionDataApplicationCommand>();
        j.at("data").get_to(*data);
        interaction.data = data;
    }
    else if (interaction.type == InteractionType::MODAL_SUBMIT)
    {
        // todo: 
    }
    map_from_json(j, "guild_id", interaction.guildId);
    map_from_json(j, "channel_id", interaction.guildId);
    map_from_json(j, "member", interaction.guildMember);
    map_from_json(j, "user", interaction.user);

    if (interaction.guildId.has_value() && interaction.guildMember.has_value())
    {
        std::optional<adb::types::SFID> userId;
        if (interaction.user.has_value())
        {
            userId = interaction.user.value().id;
        }
        gm_parse_avatar(interaction.guildId.value(), userId, j["member"], interaction.guildMember.value());
    }

    j.at("token").get_to(interaction.token);
    j.at("version").get_to(interaction.version);
    map_from_json(j, "message", interaction.message);
    if (j.contains("locale"))
    {
        std::string str;
        j.at("locale").get_to(str);
        adb::resource::Locale locale;
        adb::resource::from_string(str, locale);
        interaction.locale = locale;
    }
    if (j.contains("guild_locale"))
    {
        std::string str;
        j.at("guild_locale").get_to(str);
        adb::resource::Locale locale;
        adb::resource::from_string(str, locale);
        interaction.guildLocale = locale;
    }
}

template<>
std::optional<std::shared_ptr<InteractionDataApplicationCommand>>
    adb::api::getInteractionData<InteractionDataApplicationCommand>(const Interaction& interaction)
{
    if (!interaction.data.has_value())
        return {};
    if (interaction.type != InteractionType::APPLICATION_COMMAND &&
        interaction.type != InteractionType::APPLICATION_COMMAND_AUTOCOMPLETE)
        return {};
    if (!interaction.data.value())
        return nullptr;
    return std::static_pointer_cast<InteractionDataApplicationCommand>(interaction.data.value());
}

template<>
std::optional<std::shared_ptr<InteractionDataComponent>>
    adb::api::getInteractionData<InteractionDataComponent>(const Interaction& interaction)
{
    if (!interaction.data.has_value())
        return {};
    if (interaction.type != InteractionType::MESSAGE_COMPONENT)
        return {};
    if (!interaction.data.value())
        return nullptr;
    return std::static_pointer_cast<InteractionDataComponent>(interaction.data.value());
}

template<>
std::optional<std::shared_ptr<InteractionDataModal>>
    adb::api::getInteractionData<InteractionDataModal>(const Interaction& interaction)
{
    if (!interaction.data.has_value())
        return {};
    if (interaction.type != InteractionType::MODAL_SUBMIT)
        return {};
    if (!interaction.data.value())
        return nullptr;
    return std::static_pointer_cast<InteractionDataModal>(interaction.data.value());
}