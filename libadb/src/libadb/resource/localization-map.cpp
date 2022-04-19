#include <libadb/resource/localization-map.hpp>
#include <nlohmann/json.hpp>
using namespace adb::resource;

void adb::resource::to_json(nlohmann::json& j, const LocalizationMap& locMap)
{
    std::unordered_map<std::string, std::string> result;
    for (auto &pair : locMap)
    {
        result.insert_or_assign(to_string(pair.first), pair.second);
    }
    j = result;
}

void adb::resource::from_json(const nlohmann::json& j, LocalizationMap& locMap)
{
    std::unordered_map<std::string, std::string> input;
    j.get_to(input);
    for (auto &pair : input)
    {
        Locale loc;
        from_string(pair.first, loc);
        locMap.insert_or_assign(loc, pair.second);
    }
}