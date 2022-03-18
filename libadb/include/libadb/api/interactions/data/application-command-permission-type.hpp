#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Application Command Permission Type
     * @details https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permission-type
     */
    enum class ApplicationCommandPermissionType : uint32_t
    {
        ROLE = 1,
        USER = 2
    };
}