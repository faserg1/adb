#include <libadb/types/snowflake.hpp>
#include <nlohmann/json.hpp>
#include <chrono>
using namespace adb::types;

namespace
{
    uint16_t internalProcessIncrement = 0;
}

SFID::SFID() : id_(0)
{
    
}

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

SFID SFID::create(uint8_t workerId, uint8_t processId)
{
    SFID newId {};
    auto currentTime = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    auto duration = currentTime.time_since_epoch();
    // Discord Epoch https://discord.com/developers/docs/reference#snowflakes-snowflake-id-format-structure-left-to-right
    newId.idParts_.timestamp = duration.count() - 1420070400000;
    newId.idParts_.internalWorkerId = workerId;
    newId.idParts_.internalProcessId = processId;
    newId.idParts_.incremental = internalProcessIncrement++;
    return newId;
}

SFID::operator uint64_t() const
{
    return id_;
}

SFID::operator bool() const
{
    return static_cast<bool>(id_);
}

std::strong_ordering SFID::operator<=>(const SFID &other) const
{
    return id_ <=> other.id_;
}

bool SFID::operator==(const SFID &other) const
{
    return id_ == other.id_;
}

bool SFID::operator!=(const SFID &other) const
{
    return id_ != other.id_;
}

void adb::types::to_json(nlohmann::json& j, const SFID& id)
{
    j = id.to_string();
}

void adb::types::from_json(const nlohmann::json& j, SFID& id)
{
    id = SFID{j.get<std::string>()};
}