#include <libadb/api/message/data/send-message.hpp>
#include <nlohmann/json.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <libadb/types/helpers/json-enum.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const SendMessageParams& params)
{
    j = nlohmann::json {};
    map_to_json(j, "content", params.content);
    map_to_json(j, "tts", params.tts);
    map_to_json(j, "embeds", params.embeds);
    map_to_json(j, "allowed_mentions", params.allowedMentions);
    map_to_json(j, "message_reference", params.messageReference);
    map_to_json(j, "components", params.components);
    map_to_json(j, "sticker_ids", params.stickerIds);
    map_to_json(j, "attachments", params.attachments);
    // files[n] do not serialized to json
    // payload_json do not serialized to json
    j["flags"] = params.flags;
}

void adb::api::from_json(const nlohmann::json& j, SendMessageParams& params)
{

}