#include <libadb/api/application/data/install-params.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const InstallParams& params)
{
    j = nlohmann::json
    {
        { "scopes", params.scopes },
        { "permissions", to_string(params.permissions) }
    };
}

void adb::api::from_json(const nlohmann::json& j, InstallParams& params)
{
    j.at("scopes").get_to(params.scopes);
    from_string(j.at("permissions").get<std::string>(), params.permissions);
}
