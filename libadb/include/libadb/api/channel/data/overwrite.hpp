#pragma once

#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>
#include <libadb/api/permissions/permissions.hpp>

namespace adb::api
{
    /// Overwrite permissions for either 0 (role) or 1 (member)
    /// @see Overwrite
    enum class OverwriteType
    {
        Role = 0,
        Member = 1
    };

    /**
     * @brief Overwrite Permissions object
     * @details https://discord.com/developers/docs/resources/channel#overwrite-object
     */
    struct Overwrite
    {
        /// role or user id
        adb::types::SFID id;
        /// either 0 (role) or 1 (member)
        OverwriteType type;
        /// permission bit set
        Permissions allow;
        /// permission bit set
        Permissions deny;
    };

    void to_json(nlohmann::json& j, const Overwrite& ow);
    void from_json(const nlohmann::json& j, Overwrite& ow);
}