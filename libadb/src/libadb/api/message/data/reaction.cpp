#include <libadb/api/message/data/reaction.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Reaction& reaction)
{
    j = nlohmann::json
    {
        {"count", reaction.count},
        {"me", reaction.me},
        {"emoji", reaction.emoji},
    };
}

void adb::api::from_json(const nlohmann::json& j, Reaction& reaction)
{
    j.at("count").get_to(reaction.count);
    j.at("me").get_to(reaction.me);
    j.at("emoji").get_to(reaction.emoji);
}