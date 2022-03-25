#include <libadb/api/permissions/role-tags.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const RoleTags& tags)
{
    j = nlohmann::json {};
    map_to_json(j, "bot_id", tags.botId);
    map_to_json(j, "integration_id", tags.integrationId);
    if (tags.premiumSubscriber)
        j["premium_subscriber"] = nullptr;
}

void adb::api::from_json(const nlohmann::json& j, RoleTags& tags)
{
    map_from_json(j, "bot_id", tags.botId);
    map_from_json(j, "integration_id", tags.integrationId);
    tags.premiumSubscriber = j.contains("premium_subscriber");
}