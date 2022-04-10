#include <libadb/api/guild/data/welcome-screen.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const WelcomeScreen& welcomeScreen)
{
    j = nlohmann::json
    {
        {"description", welcomeScreen.description},
        {"welcome_channels", welcomeScreen.welcomeChannels}
    };
}

void adb::api::from_json(const nlohmann::json& j, WelcomeScreen& welcomeScreen)
{
    j.at("description").get_to(welcomeScreen.description);
    j.at("welcome_channels").get_to(welcomeScreen.welcomeChannels);
}