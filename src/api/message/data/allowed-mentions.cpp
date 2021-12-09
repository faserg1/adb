#include "allowed-mentions.hpp"
#include <string>
#include <nlohmann/json.hpp>
using namespace adb::api;

namespace
{
    constexpr const std::string_view TypeRoles = "roles";
    constexpr const std::string_view TypeUsers = "users";
    constexpr const std::string_view TypeEveryone = "everyone";
}

void adb::api::to_json(nlohmann::json& j, const AllowedMentions& allowedMention)
{
    std::vector<std::string_view> parse;
    parse.reserve(3);
    if (static_cast<uint32_t>(allowedMention.parse) & static_cast<uint32_t>(AllowedMentionsType::Roles))
        parse.push_back(TypeRoles);
    if (static_cast<uint32_t>(allowedMention.parse) & static_cast<uint32_t>(AllowedMentionsType::Users))
        parse.push_back(TypeUsers);
    if (static_cast<uint32_t>(allowedMention.parse) & static_cast<uint32_t>(AllowedMentionsType::Everyone))
        parse.push_back(TypeEveryone);
    j =
    {
        {"parse", parse}
    };
    if (allowedMention.roles.has_value())
        j["roles"] = allowedMention.roles.value();
    if (allowedMention.users.has_value())
        j["users"] = allowedMention.users.value();
    if (allowedMention.repliedUser.has_value())
        j["replied_user"] = allowedMention.repliedUser.value();
}

void adb::api::from_json(const nlohmann::json& j, AllowedMentions& allowedMention)
{
    if (j.at("parse").contains(TypeRoles))
        allowedMention.parse |= AllowedMentionsType::Roles;
}