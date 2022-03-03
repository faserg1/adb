#include <libadb/api/gateway/data/payload.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-optional.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const Payload& payload)
{
    j["op"] = payload.op;
    j["d"] = payload.data;
    j["s"] = payload.sequence;
    j["t"] = payload.eventName;
}

void adb::api::from_json(const nlohmann::json& j, Payload& payload)
{
    j.at("op").get_to(payload.op);
    if (j.contains("d"))
        j.at("d").get_to(payload.data);
    j.at("s").get_to(payload.sequence);
    j.at("t").get_to(payload.eventName);
}