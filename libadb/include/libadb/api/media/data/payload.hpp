#pragma once

#include <libadb/api/media/data/opcode.hpp>
#include <nlohmann/json.hpp>
#include <libadb/libadb.hpp>

namespace adb::api
{
    struct MediaPayload
    {
        MediaOpCode opCode;
        nlohmann::json data;
    };

    LIBADB_API void to_json(nlohmann::json& j, const MediaPayload& payload);
    LIBADB_API void from_json(const nlohmann::json& j, MediaPayload& payload);
}