#include <libadb/api/message/data/edit-message.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-enum.hpp>
#include <libadb/types/helpers/json-nullable.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const EditMessageParams& params)
{
    j = nlohmann::json {};
    map_to_json(j, "content", params.content);
    map_to_json(j, "embeds", params.embeds);
    map_to_json(j, "flags", params.flags);
    map_to_json(j, "allowed_mentions", params.allowedMentions);
    map_to_json(j, "components", params.components);
    map_to_json(j, "attachments", params.attachments);
    
    // files[n] do not serialized to json
    // payload_json do not serialized to json
}
