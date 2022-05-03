#include <libadb/api/application/data/application.hpp>
#include <libadb/resource/image-resolver.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::resource;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Application& app)
{
    j = nlohmann::json
    {
        { "id", app.id },
        { "name", app.name },
        { "icon", app.icon ? app.icon->getName() : nullptr },
        { "description", app.description },
    };
    map_to_json(j, "rpc_regions", app.rpcRegions);
    j["bot_public"] = app.botPublic;
    j["bot_require_code_grant"] = app.botRequireCodeGrant;
    map_to_json(j, "terms_of_service_url", app.termsOfServiceUrl);
    map_to_json(j, "privacy_policy_url", app.privacyPolicyUrl);
    map_to_json(j, "owner", app.owner);
    j["verify_key"] = app.verifyKey;
    j["team"] = app.team;
    map_to_json(j, "guild_id", app.guildId);
    map_to_json(j, "primary_sku_id", app.primarySkuId);
    map_to_json(j, "slug", app.slug);
    if (app.coverImage.has_value())
        j["cover_image"] = app.coverImage->getName();
    map_to_json(j, "flags", app.flags);
    map_to_json(j, "tags", app.tags);
    map_to_json(j, "install_params", app.installParams);
    map_to_json(j, "custom_install_url", app.customInstallUrl);
}

void adb::api::from_json(const nlohmann::json& j, Application& app)
{
    j.at("id").get_to(app.id);
    j.at("name").get_to(app.name);
    if (!j.at("icon").is_null())
        app.icon = ImageResolver::getApplicationIcon(app.id, j.at("icon").get<std::string>());
    j.at("description").get_to(app.description);
    map_from_json(j, "rpc_regions", app.rpcRegions);
    j.at("bot_public").get_to(app.botPublic);
    j.at("bot_require_code_grant").get_to(app.botRequireCodeGrant);
    map_from_json(j, "terms_of_service_url", app.termsOfServiceUrl);
    map_from_json(j, "privacy_policy_url", app.privacyPolicyUrl);
    map_from_json(j, "owner", app.owner);
    j.at("verify_key").get_to(app.verifyKey);
    j.at("team").get_to(app.team);
    map_from_json(j, "guild_id", app.guildId);
    map_from_json(j, "primary_sku_id", app.primarySkuId);
    map_from_json(j, "slug", app.slug);
    if (j.contains("cover_image"))
        app.coverImage = ImageResolver::getApplicationCover(app.id, j.at("cover_image").get<std::string>());
    map_from_json(j, "flags", app.flags);
    map_from_json(j, "tags", app.tags);
    map_from_json(j, "install_params", app.installParams);
    map_from_json(j, "custom_install_url", app.customInstallUrl);
}
