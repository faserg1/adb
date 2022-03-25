#include <libadb/api/guild/data/create-guild-role-params.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const CreateGuildRoleParams& params)
{
    map_to_json(j, "name", params.name);
    std::optional<std::string> permissions;
    if (params.permissions.has_value())
        permissions = to_string(params.permissions.value());
    map_to_json(j, "permissions", permissions);
    map_to_json(j, "color", params.color);
    map_to_json(j, "hoist", params.hoist);
    map_to_json(j, "icon", params.icon);
    map_to_json(j, "unicode_emoji", params.unicodeEmoji);
    map_to_json(j, "mentionable", params.mentionable);
}

void adb::api::from_json(const nlohmann::json& j, CreateGuildRoleParams& params)
{
    map_from_json(j, "name", params.name);
    std::optional<std::string> strPermissions;
    map_from_json(j, "permissions", strPermissions);
    if (strPermissions.has_value())
    {
        Permissions permissions;
        from_string(strPermissions.value(), permissions);
        params.permissions = permissions;
    }
    map_from_json(j, "color", params.color);
    map_from_json(j, "hoist", params.hoist);
    map_from_json(j, "icon", params.icon);
    map_from_json(j, "unicode_emoji", params.unicodeEmoji);
    map_from_json(j, "mentionable", params.mentionable);
}