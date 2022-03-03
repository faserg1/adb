#include <libadb/api/interactions/data/interaction.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Interaction& interaction)
{

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
    else if (interaction.type == InteractionType::APPLICATION_COMMAND)
    {
        auto data = std::make_shared<InteractionDataApplicationCommand>();
        j.at("data").get_to(*data);
        interaction.data = data;
    }
    else if (interaction.type == InteractionType::MODAL_SUBMIT)
    {

    }
    map_from_json(j, "guild_id", interaction.guildId);
    map_from_json(j, "channel_id", interaction.guildId);
    map_from_json(j, "member", interaction.guildMember);
    map_from_json(j, "user", interaction.user);
    j.at("token").get_to(interaction.token);
    j.at("version").get_to(interaction.version);
    map_from_json(j, "message", interaction.message);
    map_from_json(j, "locale", interaction.locale);
    map_from_json(j, "guild_locale", interaction.guildLocale);
}