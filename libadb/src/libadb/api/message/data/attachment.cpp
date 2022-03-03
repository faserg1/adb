#include <libadb/api/message/data/attachment.hpp>
#include <libadb/types/helpers/json-optional.hpp>
#include <nlohmann/json.hpp>
using namespace adb::api;
using namespace adb::types;

void adb::api::to_json(nlohmann::json& j, const SendAttachment& attachment)
{
    j = nlohmann::json {};
    j["id"] = attachment.id;
    map_to_json(j, "filename", attachment.filename);
    map_to_json(j, "description", attachment.description);
    map_to_json(j, "content_type", attachment.contentType);
    map_to_json(j, "size", attachment.size);
    map_to_json(j, "url", attachment.url);
    map_to_json(j, "proxy_url", attachment.proxyUrl);
    map_to_json(j, "height", attachment.height);
    map_to_json(j, "width", attachment.width);
    map_to_json(j, "ephemeral", attachment.ephemeral);
}

void adb::api::from_json(const nlohmann::json& j, SendAttachment& attachment)
{
    j.at("id").get_to(attachment.id);
    map_from_json(j, "filename", attachment.filename);
    map_from_json(j, "description", attachment.description);
    map_from_json(j, "content_type", attachment.contentType);
    map_from_json(j, "size", attachment.size);
    map_from_json(j, "url", attachment.url);
    map_from_json(j, "proxy_url", attachment.proxyUrl);
    map_from_json(j, "height", attachment.height);
    map_from_json(j, "width", attachment.width);
    map_from_json(j, "ephemeral", attachment.ephemeral);
}

void adb::api::to_json(nlohmann::json& j, const Attachment& attachment)
{
    j = nlohmann::json {};
    j["id"] = attachment.id;
    j["filename"] = attachment.filename;
    map_to_json(j, "description", attachment.description);
    map_to_json(j, "content_type", attachment.contentType);
    j["size"] = attachment.size;
    j["url"] = attachment.url;
    j["proxyUrl"] = attachment.proxyUrl;
    map_to_json(j, "height", attachment.height);
    map_to_json(j, "width", attachment.width);
    map_to_json(j, "ephemeral", attachment.ephemeral);
}

void adb::api::from_json(const nlohmann::json& j, Attachment& attachment)
{
    j.at("id").get_to(attachment.id);
    j.at("filename").get_to(attachment.filename);
    map_from_json(j, "description", attachment.description);
    map_from_json(j, "content_type", attachment.contentType);
    j.at("size").get_to(attachment.size);
    j.at("url").get_to(attachment.url);
    j.at("proxy_url").get_to(attachment.proxyUrl);
    map_from_json(j, "height", attachment.height);
    map_from_json(j, "width", attachment.width);
    map_from_json(j, "ephemeral", attachment.ephemeral);
}