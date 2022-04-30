#include <libadb/api/guild/data/unavailable-guild.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const UnavailableGuild& guild)
{
    j = nlohmann::json
    {
        { "id", guild.id },
        { "unavailable", guild.unavailable },
    };
}

void adb::api::from_json(const nlohmann::json& j, UnavailableGuild& guild)
{
    j.at("id").get_to(guild.id);
    j.at("unavailable").get_to(guild.unavailable);
}