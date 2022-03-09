#pragma once

namespace adb::api
{
    /**
     * @brief Video Quality Mode
     * @details https://discord.com/developers/docs/resources/channel#channel-object-video-quality-modes
     */
    enum class VideoQualityMode
    {
        /// Discord chooses the quality for optimal performance
        AUTO = 1,
        /// 720p
        FULL = 2,
    };
}