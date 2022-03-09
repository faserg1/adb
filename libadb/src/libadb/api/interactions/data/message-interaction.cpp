#include <libadb/api/interactions/data/message-interaction.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-enum.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const MessageInteraction& msgInteraction)
{
    j = nlohmann::json
    {
        {"id", msgInteraction.id},
        {"type", msgInteraction.type},
        {"name", msgInteraction.name},
        {"user", msgInteraction.user},
    };
    map_to_json(j, "member", msgInteraction.guildMember);
}

void adb::api::from_json(const nlohmann::json& j, MessageInteraction& msgInteraction)
{
    j.at("id").get_to(msgInteraction.id);
    j.at("type").get_to(msgInteraction.type);
    j.at("name").get_to(msgInteraction.name);
    j.at("user").get_to(msgInteraction.user);
    j.at("id").get_to(msgInteraction.id);
    map_from_json(j, "member", msgInteraction.guildMember);
}