#pragma once

#include <string>
#include <optional>
#include <chrono>
#include <vector>
#include <libadb/types/color.hpp>
#include <libadb/types/time.hpp>
#include <nlohmann/json_fwd.hpp>

namespace adb::api
{
    /**
     * @brief Embed Footer Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
     * @details https://discord.com/developers/docs/resources/channel#embed-limits
     */
    struct EmbedFooter
    {
        /// footer text, up to 2048 characters
        std::string text;
        /// url of footer icon (only supports http(s) and attachments)
        std::optional<std::string> iconUrl;
        /// a proxied url of footer icon
        std::optional<std::string> proxyIconUrl;
    };

    struct EmbedImage
    {
        /// source url of image (only supports http(s) and attachments)
        std::optional<std::string> url;
        /// a proxied url of the image
        std::optional<std::string> proxyUrl;
        /// height of image
        std::optional<size_t> width;
        /// width of image
        std::optional<size_t> height; 
    };

    /**
     * @brief Embed Thumbnail Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
     */
    struct EmbedThumbnail
    {
        /// source url of thumbnail (only supports http(s) and attachments)
        std::string url;
        /// a proxied url of the thumbnail
        std::optional<std::string> proxyUrl;
        /// height of thumbnail
        std::optional<size_t> width;
        /// width of thumbnail
        std::optional<size_t> height;
    };

    /**
     * @brief Embed Video Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
     */
    struct EmbedVideo
    {
        /// source url of video
        std::optional<std::string> url;
        /// a proxied url of the video
        std::optional<std::string> proxyUrl;
        /// height of video
        std::optional<size_t> width;
        /// width of video
        std::optional<size_t> height; 
    };

    /**
     * @brief Embed Provider Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
     */
    struct EmbedProvider
    {
        /// name of provider
        std::optional<std::string> name;
        /// url of provider
        std::optional<std::string> url;
    };

    /**
     * @brief Embed Author Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
     * @details https://discord.com/developers/docs/resources/channel#embed-limits
     */
    struct EmbedAuthor
    {
        /// name of author, up to 256 characters
        std::string name;
        /// url of author
        std::optional<std::string> url;
        /// url of author icon (only supports http(s) and attachments)
        std::optional<std::string> iconUrl;
        /// a proxied url of author icon
        std::optional<std::string> proxyIconUrl;
    };

    /**
     * @brief Embed Field Structure
     * @details https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
     * @details https://discord.com/developers/docs/resources/channel#embed-limits
     */
    struct EmbedField
    {
        /// name of the field, up to 256 characters
        std::string name;
        /// value of the field, up to 1024 characters
        std::string value;
        /// whether or not this field should display inline
        std::optional<bool> isInline;
    };

    /**
     * @brief Embed Object
     * @details https://discord.com/developers/docs/resources/channel#embed-object
     * @details https://discord.com/developers/docs/resources/channel#embed-limits
     */
    struct Embed
    {
        /// title of embed, up to 256 characters
        std::optional<std::string> title;
        /// Embed Types ["rich", "image", "video", "gifv", "article", "link"]
        /// Deprecated
        std::optional<std::string> type;
        /// description of embed, up to 4096 characters
        std::optional<std::string> description;
        /// url of embed
        std::optional<std::string> url;
        /// timestamp of embed content
        std::optional<adb::types::TimePoint> timestamp;
        /// color code of the embed
        std::optional<adb::types::Color> color;
        /// footer information
        std::optional<EmbedFooter> footer;
        /// image information
        std::optional<EmbedImage> image;
        /// thumbnail information
        std::optional<EmbedThumbnail> thumbnail;
        /// video information
        std::optional<EmbedVideo> video;
        /// provider information
        std::optional<EmbedProvider> provider;
        /// author information
        std::optional<EmbedAuthor> author;
        /// fields information, up to 25 objects
        std::optional<std::vector<EmbedField>> fields;
    };

    void to_json(nlohmann::json& j, const EmbedFooter& footer);
    void from_json(const nlohmann::json& j, EmbedFooter& footer);

    void to_json(nlohmann::json& j, const EmbedImage& image);
    void from_json(const nlohmann::json& j, EmbedImage& image);

    void to_json(nlohmann::json& j, const EmbedThumbnail& thumbnail);
    void from_json(const nlohmann::json& j, EmbedThumbnail& thumbnail);

    void to_json(nlohmann::json& j, const EmbedVideo& video);
    void from_json(const nlohmann::json& j, EmbedVideo& video);

    void to_json(nlohmann::json& j, const EmbedProvider& provider);
    void from_json(const nlohmann::json& j, EmbedProvider& provider);

    void to_json(nlohmann::json& j, const EmbedAuthor& author);
    void from_json(const nlohmann::json& j, EmbedAuthor& author);

    void to_json(nlohmann::json& j, const EmbedField& field);
    void from_json(const nlohmann::json& j, EmbedField& field);

    void to_json(nlohmann::json& j, const Embed& embed);
    void from_json(const nlohmann::json& j, Embed& embed);
}