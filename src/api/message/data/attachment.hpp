#pragma once

#include <optional>
#include <string>
#include <vector>
#include <nlohmann/json_fwd.hpp>
#include <types/snowflake.hpp>

namespace adb::api
{
    /**
     * @brief Partial Attachment Object
     * @details https://discord.com/developers/docs/resources/channel#attachment-object
     */
    struct SendAttachment
    {
        /// attachment id
        size_t id;
        /// name of file attached
        std::optional<std::string> filename;
        /// description for the file
        std::optional<std::string> description;
        /// the attachment's media type
        std::optional<std::string> contentType;
        /// size of file in bytes
        std::optional<size_t> size;
        /// source url of file
        std::optional<std::string> url;
        /// a proxied url of file
        std::optional<std::string> proxyUrl;
        /// height of file (if image)
        std::optional<size_t> height;
        /// width of file (if image)
        std::optional<size_t> width;
        /// whether this attachment is ephemeral
        std::optional<bool> ephemeral;
        /// attached file
        std::optional<std::vector<std::byte>> fileContent;
    };

    /**
     * @brief Attachment Object
     * @details https://discord.com/developers/docs/resources/channel#attachment-object
     */
    struct Attachment
    {
        /// attachment id
        adb::types::SFID id;
        /// name of file attached
        std::string filename;
        /// description for the file
        std::optional<std::string> description;
        /// the attachment's media type
        std::optional<std::string> contentType;
        /// size of file in bytes
        size_t size;
        /// source url of file
        std::string url;
        /// a proxied url of file
        std::string proxyUrl;
        /// height of file (if image)
        std::optional<size_t> height;
        /// width of file (if image)
        std::optional<size_t> width;
        /// whether this attachment is ephemeral
        std::optional<bool> ephemeral;
    };

    void to_json(nlohmann::json& j, const SendAttachment& attachment);
    void from_json(const nlohmann::json& j, SendAttachment& attachment);

    void to_json(nlohmann::json& j, const Attachment& attachment);
    void from_json(const nlohmann::json& j, Attachment& attachment);
}