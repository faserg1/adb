#include <libadb/api/permissions/role.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/resource/image-resolver.hpp>

using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Role& role)
{
    j = nlohmann::json
    {
        {"id", role.id},
        {"name", role.name},
        {"color", role.color},
        {"hoist", role.hoist},
    };
    if (role.icon.has_value())
    {
        if (role.icon.value())
            j["icon"] = role.icon.value()->getName();
        else
            j["icon"] = nullptr;
    }
    map_to_json(j, "unicode_emoji", role.unicodeEmoji);
    j["position"] = role.position;
    j["permissions"] = to_string(role.permissions);
    j["managed"] = role.managed;
    j["mentionable"] = role.mentionable;
    map_to_json(j, "tags", role.tags);
}

void adb::api::from_json(const nlohmann::json& j, Role& role)
{
    j.at("id").get_to(role.id);
    j.at("name").get_to(role.name);
    j.at("color").get_to(role.color);
    j.at("hoist").get_to(role.hoist);

    std::optional<adb::types::Nullable<std::string>> iconHash;
    if (iconHash.has_value() && iconHash.value())
    {
        role.icon = adb::resource::ImageResolver::getRoleIcon(role.id, *iconHash.value());
    }

    map_from_json(j, "unicode_emoji", role.unicodeEmoji);
    j.at("position").get_to(role.position);

    std::string strPermissions;
    j.at("permissions").get_to(strPermissions);
    Permissions permissions;
    adb::api::from_string(strPermissions, permissions);
    role.permissions = permissions;

    j.at("managed").get_to(role.managed);
    j.at("mentionable").get_to(role.mentionable);
    map_from_json(j, "tags", role.tags);
}