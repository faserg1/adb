#include <libadb/api/permissions/permissions.hpp>
using namespace adb::api;

void adb::api::from_string(const std::string &str, Permissions &permissions)
{
    permissions = std::atoll(str.data());
}

std::string adb::api::to_string(Permissions permissions)
{
    return std::to_string(permissions);
}