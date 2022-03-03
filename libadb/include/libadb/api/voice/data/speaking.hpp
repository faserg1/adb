#pragma once

#include <cstdint>
#include <libadb/types/helpers/enums.hpp>
#include <nlohmann/json_fwd.hpp>
#include <libadb/types/snowflake.hpp>

namespace adb::api
{
    /**
     * @brief Speaking flags
     * @details https://discord.com/developers/docs/topics/voice-connections#speaking
     */
    enum class SpeakingFlag : uint16_t
    {
        /// Normal transmission of voice audio
        Microphone = (1 << 0),
        /// Transmission of context audio for video, no speaking indicator
        Soundshare = (1 << 1),
        /// Priority speaker, lowering audio of other speakers
        Priority = (1 << 2),
    };

    ADB_ENUM_FLAGS_OPERATORS(SpeakingFlag, SpeakingFlags, uint16_t)

    /**
     * @brief Speaking Payload, that should be sended to server
     * NO DETAILS!!! I NEED DOCUMENTAION!!!
     */
    struct SpeakingSendPayload
    {
        /// Speaking flags
        SpeakingFlags speaking;
        /// ??? wut da heck
        uint16_t delay;
        /// The SSRC (from Ready Event)
        uint16_t ssrc;
    };

    void to_json(nlohmann::json& j, const SpeakingSendPayload& speaking);
    void from_json(const nlohmann::json& j, SpeakingSendPayload& speaking);

    /**
     * @brief Speaking Payload, that should be received from server
     * NO DETAILS!!! I NEED DOCUMENTAION!!!
     */
    struct SpeakingReceivePayload
    {
        /// Is user speaking
        bool speaking;
        /// User ID, which switch speaking
        adb::types::SFID userId;
        /// The SSRC
        uint16_t ssrc;
    };

    void to_json(nlohmann::json& j, const SpeakingReceivePayload& speaking);
    void from_json(const nlohmann::json& j, SpeakingReceivePayload& speaking);
}