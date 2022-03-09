#include <libadb/api/sticker/data/sticker-item.hpp>
#include <nlohmann/json.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const StickerItem& item)
{
    j = nlohmann::json
    {
        {"id", item.id},
        {"name", item.name},
        {"format_type", item.formatType},
    };
}

void adb::api::from_json(const nlohmann::json& j, StickerItem& item)
{
    j.at("id").get_to(item.id);
    j.at("name").get_to(item.name);
    j.at("format_type").get_to(item.formatType);
}