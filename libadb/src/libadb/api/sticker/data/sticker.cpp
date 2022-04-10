#include <libadb/api/sticker/data/sticker.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <fmt/format.h>
#include <regex>
using namespace adb::api;
using namespace adb::types;

namespace 
{
    void getTags(const std::string &strTags, std::vector<std::string> &tags)
    {
        using re_iterator = std::regex_iterator<std::string::const_iterator>;
        using re_iterated = re_iterator::value_type;
        static std::regex re("([\\\\\\w\\s]+),?\\s*");
        re_iterator rit(strTags.begin(), strTags.end(), re);
        re_iterator rend;

        std::transform(rit, rend, std::back_inserter(tags), [](const re_iterated& it)
        {
            return it[1];
        });
    }
}

void adb::api::to_json(nlohmann::json& j, const Sticker& sticker)
{
    j = nlohmann::json
    {
        {"id", sticker.id}
    };
    map_to_json(j, "pack_id", sticker.packId);
    j["name"] = sticker.name;
    map_to_json(j, "description", sticker.description);
    j["tags"] = fmt::format("{}", fmt::join(sticker.tags, ", "));
    j["type"] = sticker.type;
    j["format_type"] = sticker.formatType;
    map_to_json(j, "available", sticker.available);
    map_to_json(j, "guild_id", sticker.guildId);
    map_to_json(j, "user", sticker.user);
    map_to_json(j, "sort_value", sticker.sortValue);
}

void adb::api::from_json(const nlohmann::json& j, Sticker& sticker)
{
    j.at("id").get_to(sticker.id);
    map_from_json(j, "pack_id", sticker.packId);
    j.at("name").get_to(sticker.name);
    map_from_json(j, "description", sticker.description);
    getTags(j.at("tags").get<std::string>(), sticker.tags);
    j.at("type").get_to(sticker.type);
    j.at("format_type").get_to(sticker.formatType);
    map_from_json(j, "available", sticker.available);
    map_from_json(j, "guild_id", sticker.guildId);
    map_from_json(j, "user", sticker.user);
    map_from_json(j, "sort_value", sticker.sortValue);
}