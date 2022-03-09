#include <libadb/api/channel/data/thread-metadata.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
#include <libadb/types/helpers/json-chrono.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const ThreadMetadata& metadata)
{
    j = nlohmann::json
    {
        {"archived", metadata.archived},
        {"auto_archive_duration", metadata.autoArchiveDuration},
        {"archive_timestamp", metadata.archiveTimestamp},
        {"locked", metadata.locked},
        {"invitable", metadata.invitable},
        {"create_timestamp", metadata.createTimestamp},
    };
}

void adb::api::from_json(const nlohmann::json& j, ThreadMetadata& metadata)
{
    j.at("archived").get_to(metadata.archived);
    j.at("auto_archive_duration").get_to(metadata.autoArchiveDuration);
    j.at("archive_timestamp").get_to(metadata.archiveTimestamp);
    j.at("locked").get_to(metadata.locked);
    map_from_json(j, "invitable", metadata.invitable);
    map_from_json(j, "create_timestamp", metadata.createTimestamp);
}