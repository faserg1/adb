#include "embed.hpp"
#include <nlohmann/json.hpp>
#include <types/helpers/json-optional.hpp>
#include <types/helpers/json-chrono.hpp>
using namespace adb::api;

void adb::api::to_json(nlohmann::json& j, const EmbedFooter& footer)
{
    j = nlohmann::json
    {
        {"text", footer.text},
        {"icon_url", footer.iconUrl},
        {"proxy_icon_url", footer.proxyIconUrl},
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedFooter& footer)
{
    j.at("text").get_to(footer.text);
    if (j.contains("icon_url"))
        j.at("icon_url").get_to(footer.iconUrl);
    if (j.contains("proxy_icon_url"))
        j.at("proxy_icon_url").get_to(footer.proxyIconUrl);
}

void adb::api::to_json(nlohmann::json& j, const EmbedImage& image)
{
    j = nlohmann::json
    {
        {"url", image.url},
        {"proxy_url", image.proxyUrl},
        {"height", image.height},
        {"width", image.width}
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedImage& image)
{
    j.at("url").get_to(image.url);
    if (j.contains("proxy_url"))
        j.at("proxy_url").get_to(image.proxyUrl);
    if (j.contains("height"))
        j.at("height").get_to(image.height);
    if (j.contains("width"))
        j.at("width").get_to(image.width);
}

void adb::api::to_json(nlohmann::json& j, const EmbedThumbnail& thumbnail)
{
    j = nlohmann::json
    {
        {"url", thumbnail.url},
        {"proxy_url", thumbnail.proxyUrl},
        {"width", thumbnail.width},
        {"height", thumbnail.height}
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedThumbnail& thumbnail)
{
    j.at("url").get_to(thumbnail.url);
    if (j.contains("proxy_url"))
        j.at("proxy_url").get_to(thumbnail.proxyUrl);
    if (j.contains("width"))
        j.at("width").get_to(thumbnail.width);
    if (j.contains("height"))
        j.at("height").get_to(thumbnail.height);
}

void adb::api::to_json(nlohmann::json& j, const EmbedVideo& video)
{
    j = nlohmann::json
    {
        {"url", video.url},
        {"proxy_url", video.proxyUrl},
        {"width", video.width},
        {"height", video.height}
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedVideo& video)
{
    if (j.contains("url"))
        j.at("url").get_to(video.url);
    if (j.contains("proxy_url"))
        j.at("proxy_url").get_to(video.proxyUrl);
    if (j.contains("width"))
        j.at("width").get_to(video.width);
    if (j.contains("height"))
        j.at("height").get_to(video.height);
}

void adb::api::to_json(nlohmann::json& j, const EmbedProvider& provider)
{
    j = nlohmann::json
    {
        {"name", provider.name},
        {"url", provider.url},
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedProvider& provider)
{
    if (j.contains("name"))
        j.at("name").get_to(provider.name);
    if (j.contains("url"))
        j.at("url").get_to(provider.url);
}

void adb::api::to_json(nlohmann::json& j, const EmbedAuthor& author)
{
    j = nlohmann::json
    {
        {"name", author.name},
        {"url", author.url},
        {"icon_url", author.iconUrl},
        {"proxy_icon_url", author.proxyIconUrl}
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedAuthor& author)
{
    j.at("name").get_to(author.name);
    if (j.contains("url"))
        j.at("url").get_to(author.url);
    if (j.contains("icon_url"))
        j.at("icon_url").get_to(author.iconUrl);
    if (j.contains("proxy_icon_url"))
        j.at("proxy_icon_url").get_to(author.proxyIconUrl);
}

void adb::api::to_json(nlohmann::json& j, const EmbedField& field)
{
    j = nlohmann::json
    {
        {"name", field.name},
        {"value", field.value},
        {"inline", field.isInline},
    };
}

void adb::api::from_json(const nlohmann::json& j, EmbedField& field)
{
    j.at("name").get_to(field.name);
    j.at("value").get_to(field.value);
    if (j.contains("inline"))
        j.at("inline").get_to(field.isInline);
}

void adb::api::to_json(nlohmann::json& j, const Embed& embed)
{
    j = nlohmann::json
    {
        {"title", embed.title},
        {"type", embed.type},
        {"description", embed.description},
        {"url", embed.url},
        {"timestamp", embed.timestamp},
        {"color", embed.color},
        {"footer", embed.footer},
        {"image", embed.image},
        {"thumbnail", embed.thumbnail},
        {"video", embed.video},
        {"provider", embed.provider},
        {"author", embed.author},
        {"fields", embed.fields}
    };
}

void adb::api::from_json(const nlohmann::json& j, Embed& embed)
{
    if (j.contains("title"))
        j.at("title").get_to(embed.title);
    if (j.contains("type"))
        j.at("type").get_to(embed.type);
    if (j.contains("description"))
        j.at("description").get_to(embed.description);
    if (j.contains("url"))
        j.at("url").get_to(embed.url);
    if (j.contains("timestamp"))
        j.at("timestamp").get_to(embed.timestamp);
    if (j.contains("color"))
        j.at("color").get_to(embed.color);
    if (j.contains("footer"))
        j.at("footer").get_to(embed.footer);
    if (j.contains("image"))
        j.at("image").get_to(embed.image);
    if (j.contains("thumbnail"))
        j.at("thumbnail").get_to(embed.thumbnail);
    if (j.contains("video"))
        j.at("video").get_to(embed.video);
    if (j.contains("provider"))
        j.at("provider").get_to(embed.provider);
    if (j.contains("author"))
        j.at("author").get_to(embed.author);
    if (j.contains("fields"))
        j.at("fields").get_to(embed.fields);
}