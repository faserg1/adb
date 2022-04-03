#include <libadb/types/snowflake.hpp>
#include <nlohmann/json.hpp>
using namespace adb::types;

SFID::SFID(uint64_t id) : id_(id)
{

}

SFID::SFID(const std::string &strId) : id_(std::atoll(strId.data()))
{
}

std::string SFID::to_string() const
{
    return std::to_string(id_);
}

SFID SFID::create()
{
    return {};
}

SFID::operator uint64_t() const
{
    return id_;
}

bool SFID::operator==(const SFID &other) const
{
    return id_ == other.id_;
}

void adb::types::to_json(nlohmann::json& j, const SFID& id)
{
    j = id.to_string();
}

void adb::types::from_json(const nlohmann::json& j, SFID& id)
{
    id = j.get<std::string>();
}