#include <libadb/api/channel/data/overwrite.hpp>
#include <charconv>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const Overwrite& ow)
{
    j = nlohmann::json
    {
        {"id", ow.id},
        {"type", ow.type},
        {"allow", std::to_string(ow.allow)},
        {"deny", std::to_string(ow.deny)},
    };
}

void adb::api::from_json(const nlohmann::json& j, Overwrite& ow)
{
    j.at("id").get_to(ow.id);
    j.at("type").get_to(ow.type);
    std::string allow, deny;
    j.at("allow").get_to(allow);
    j.at("deny").get_to(deny);
    std::from_chars(allow.data(), allow.data() + allow.size(), ow.allow);
    std::from_chars(deny.data(), deny.data() + deny.size(), ow.deny);
}