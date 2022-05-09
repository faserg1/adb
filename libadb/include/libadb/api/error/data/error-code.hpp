#pragma once

#include <cstdint>

namespace adb::api
{
    /**
     * @brief Along with the HTTP error code, our API can also return more detailed error codes through a code key in the JSON error response.
     * @details https://discord.com/developers/docs/topics/opcodes-and-status-codes#json
     */
    enum class ErrorCode : uint64_t
    {
        // General error (such as a malformed request body, amongst other things)
        GENERAL_ERROR = 0,
        // Unknown account
        UNKNOWN_ACCOUNT = 10001 ,
        // Unknown application
        UNKNOWN_APPLICATION = 10002 ,
        // Unknown channel
        UNKNOWN_CHANNEL = 10003 ,
        // Unknown guild
        UNKNOWN_GUILD = 10004 ,
        // Unknown integration
        UNKNOWN_INTEGRATION = 10005 ,
        // Unknown invite
        UNKNOWN_INVITE = 10006 ,
        // Unknown member
        UNKNOWN_MEMBER = 10007 ,
        // Unknown message
        UNKNOWN_MESSAGE = 10008 ,
        // Unknown permission overwrite
        UNKNOWN_PERMISSION_OVERWRITE = 10009 ,
        // Unknown provider
        UNKNOWN_PROVIDER = 10010 ,
        // Unknown role
        UNKNOWN_ROLE = 10011 ,
        // Unknown token
        UNKNOWN_TOKEN = 10012 ,
        // Unknown user
        UNKNOWN_USER = 10013 ,
        // Unknown emoji
        UNKNOWN_EMOJI = 10014 ,
        // Unknown webhook
        UNKNOWN_WEBHOOK = 10015 ,
        // Unknown webhook service
        UNKNOWN_WEBHOOK_SERVICE = 10016 ,
        // Unknown session
        UNKNOWN_SESSION = 10020 ,
        // Unknown ban
        UNKNOWN_BAN = 10026 ,
        // Unknown SKU
        UNKNOWN_SKU = 10027 ,
        // Unknown Store Listing
        UNKNOWN_STORE_LISTING = 10028 ,
        // Unknown entitlement
        UNKNOWN_ENTITLEMENT = 10029 ,
        // Unknown build
        UNKNOWN_BUILD = 10030 ,
        // Unknown lobby
        UNKNOWN_LOBBY = 10031 ,
        // Unknown branch
        UNKNOWN_BRANCH = 10032 ,
        // Unknown store directory layout
        UNKNOWN_STORE_DIRECTORY_LAYOUT = 10033 ,
        // Unknown redistributable
        UNKNOWN_REDISTRIBUTABLE = 10036 ,
        // Unknown gift code
        UNKNOWN_GIFT_CODE = 10038 ,
        // Unknown stream
        UNKNOWN_STREAM = 10049 ,
        // Unknown premium server subscribe cooldown
        UNKNOWN_PREMIUM_SERVER_SUBSCRIBE_COOLDOWN = 10050 ,
        // Unknown guild template
        UNKNOWN_GUILD_TEMPLATE = 10057 ,
        // Unknown discoverable server category
        UNKNOWN_DISCOVERABLE_SERVER_CATEGORY = 10059 ,
        // Unknown sticker
        UNKNOWN_STICKER = 10060 ,
        // Unknown interaction
        UNKNOWN_INTERACTION = 10062 ,
        // Unknown application command
        UNKNOWN_APPLICATION_COMMAND = 10063 ,
        // Unknown voice state
        UNKNOWN_VOICE_STATE = 10065 ,
        // Unknown application command permissions
        UNKNOWN_APPLICATION_COMMAND_PERMISSIONS = 10066 ,
        // Unknown Stage Instance
        UNKNOWN_STAGE_INSTANCE = 10067 ,
        // Unknown Guild Member Verification Form
        UNKNOWN_GUILD_MEMBER_VERIFICATION_FORM = 10068 ,
        // Unknown Guild Welcome Screen
        UNKNOWN_GUILD_WELCOME_SCREEN = 10069 ,
        // Unknown Guild Scheduled Event
        UNKNOWN_GUILD_SCHEDULED_EVENT = 10070 ,
        // Unknown Guild Scheduled Event User
        UNKNOWN_GUILD_SCHEDULED_EVENT_USER = 10071 ,
        // Unknown Tag
        UNKNOWN_TAG = 10087 ,
        // Bots cannot use this endpoint
        NOT_AUTHORIZED_USER_ONLY = 20001 ,
        // Only bots can use this endpoint
        NOT_AUTHORIZED_BOT_ONLY = 20002 ,
        // Explicit content cannot be sent to the desired recipient(s)
        EXPLICIT_CONTENT_CANNOT_BE_SENT = 20009 ,
        // You are not authorized to perform this action on this application
        NOT_AUTHORIZED_ACTION_ON_APP = 20012 ,
        // This action cannot be performed due to slowmode rate limit
        RATE_LIMIT_ACTION_SLOWMODE = 20016 ,
        // Only the owner of this account can perform this action
        NOT_AUTHORIZED_ONWER_ONLY = 20018 ,
        // This message cannot be edited due to announcement rate limits
        RATE_LIMIT_CANNOT_EDIT_MESSAGE = 20022 ,
        // The channel you are writing has hit the write rate limit
        RATE_LIMIT_CHANNEL_WRITE = 20028 ,
        // The write action you are performing on the server has hit the write rate limit
        RATE_LIMIT_SERVER_WRITE = 20029 ,
        // Your Stage topic, server name, server description, or channel names contain words that are not allowed
        BAN_WORDS = 20031 ,
        // Guild premium subscription level too low
        GUILD_LOW_PREMIUM_LEVEL = 20035 ,
        // Maximum number of guilds reached (100)
        MAX_GUILDS = 30001 ,
        // Maximum number of friends reached (1000)
        MAX_FRIENDS = 30002 ,
        // Maximum number of pins reached for the channel (50)
        MAX_CHANNEL_PINS = 30003 ,
        // Maximum number of recipients reached (10)
        MAX_RECIPIENTS = 30004 ,
        // Maximum number of guild roles reached (250)
        MAX_GUILD_ROLES = 30005 ,
        // Maximum number of webhooks reached (10)
        MAX_WEBHOOKS = 30007 ,
        // Maximum number of emojis reached
        MAX_EMOJIS = 30008 ,
        // Maximum number of reactions reached (20)
        MAX_REACTIONS = 30010 ,
        // Maximum number of guild channels reached (500)
        MAX_GUILD_CHANNELS = 30013 ,
        // Maximum number of attachments in a message reached (10)
        MAX_MESSAGE_ATTACHMENTS = 30015 ,
        // Maximum number of invites reached (1000)
        MAX_INVITES = 30016 ,
        // Maximum number of animated emojis reached
        MAX_ANIMATED_EMOJIS = 30018 ,
        // Maximum number of server members reached
        MAX_SERVER_MEMBERS = 30019 ,
        // Maximum number of server categories has been reached (5)
        MAX_SERVER_CATEGORIES = 30030 ,
        // Guild already has a template
        GUILD_ALREADY_HAS_TEMPLATE = 30031 ,
        // Max number of thread participants has been reached (1000)
        MAX_THREAD_USERS = 30033 ,
        // Maximum number of bans for non-guild members have been exceeded
        MAX_NON_GUILD_BANS = 30035 ,
        // Maximum number of bans fetches has been reached
        MAX_BAN_FETCHES = 30037 ,
        // Maximum number of uncompleted guild scheduled events reached (100)
        MAX_UNCOMPLETED_SCHEDULED_EVENTS = 30038 ,
        // Maximum number of stickers reached
        MAX_STICKERS = 30039 ,
        // Maximum number of prune requests has been reached. Try again later
        MAX_PRUNE_REQUESTS = 30040 ,
        // Maximum number of guild widget settings updates has been reached. Try again later
        MAX_GUILD_WIDGET_SETTINGS_UPDATES = 30042 ,
        // Maximum number of edits to messages older than 1 hour reached. Try again later
        MAX_MESSAGE_EDITS = 30046 ,
        // Maximum number of pinned threads in a forum channel has been reached
        MAX_PINNED_THREADS = 30047 ,
        // Maximum number of tags in a forum channel has been reached
        MAX_TAGS = 30048 ,
        // Unauthorized. Provide a valid token and try again
        UNAUTHORIZED = 40001 ,
        // You need to verify your account in order to perform this action
        UNAUTHORIZED_VERIFY_ACCOUNT = 40002 ,
        // You are opening direct messages too fast
        RATE_LIMIT_DIRECT_MESSAGES = 40003 ,
        // Send messages has been temporarily disabled
        TEMPORARY_DISABLED_SEND_MESSAGES = 40004 ,
        // Request entity too large. Try sending something smaller in size
        REQUEST_TOO_LARGE = 40005 ,
        // This feature has been temporarily disabled server-side
        TEMPORARY_DISABLED_FEATURE = 40006 ,
        // The user is banned from this guild
        BANNED_USER = 40007 ,
        // Target user is not connected to voice
        NOT_CONNECTED_TO_VOICE = 40032 ,
        // This message has already been crossposted
        ALREADY_CROSSPOSTED = 40033 ,
        // An application command with that name already exists
        COMMAND_ALREADY_EXISTS = 40041 ,
        // Interaction has already been acknowledged
        INTERACTION_ALREADY_ACK = 40060 ,
        // Tag names must be unique
        NOT_UNIQUE_NAMES = 40061 ,
        // Missing access
        MISSING_ACCESS = 50001 ,
        // Invalid account type
        INVALID_ACCOUNT_TYPE = 50002 ,
        // Cannot execute action on a DM channel
        INVALID_FOR_DM = 50003 ,
        // Guild widget disabled
        GUILD_WIDGET_DISABLED = 50004 ,
        // Cannot edit a message authored by another user
        MESSAGE_EDIT_AUTHOR = 50005 ,
        // Cannot send an empty message
        MESSAGE_EMTY = 50006 ,
        // Cannot send messages to this user
        MESSAGE_SEND_USER_DENIED = 50007 ,
        // Cannot send messages in a non-text channel
        NOT_TEXT_CHANNEL = 50008 ,
        // Channel verification level is too high for you to gain access
        CHANNEL_VERIFICATION_HIGH = 50009 ,
        // OAuth2 application does not have a bot
        APPLICATION_HAS_NO_BOT = 50010 ,
        // OAuth2 application limit reached
        APPLICATION_LIMIT = 50011 ,
        // Invalid OAuth2 state
        INVALID_OAUTH_STATE = 50012 ,
        // You lack permissions to perform that action
        NO_PERMISSIONS = 50013 ,
        // Invalid authentication token provided
        INVALID_AUTH_TOKEN = 50014 ,
        // Note was too long
        NOTE_TOO_LONG = 50015 ,
        // Provided too few or too many messages to delete. Must provide at least 2 and fewer than 100 messages to delete
        MESSAGE_DELETE_BULK_OUT_OF_BOUNDS = 50016 ,
        // A message can only be pinned to the channel it was sent in
        MESSAGE_PIN_WRONG_CHANNEL = 50019 ,
        // Invite code was either invalid or taken
        INVALID_INVITE = 50020 ,
        // Cannot execute action on a system message
        CANNOT_EXECUTE_ON_SYSTEM_MESSAGE = 50021 ,
        // Cannot execute action on this channel type
        CANNOT_EXECUTE_ON_CURRENT_CHANNEL_TYPE = 50024 ,
        // Invalid OAuth2 access token provided
        UNAUTHORIZED_INVALID_TOKEN = 50025 ,
        // Missing required OAuth2 scope
        UNAUTHORIZED_MISSING_SCOPE = 50026 ,
        // Invalid webhook token provided
        INVALID_WEBHOOK_TOKEN = 50027 ,
        // Invalid role
        INVALID_ROLE = 50028 ,
        // Invalid Recipient(s)
        INVALID_RECIPIENTS = 50033 ,
        // A message provided was too old to bulk delete
        MESSAGE_DELETE_BULK_TOO_OLD = 50034 ,
        // Invalid form body (returned for both application/json and multipart/form-data bodies), or invalid Content-Type provided
        INVALID_PAYLOAD_SENDED = 50035 ,
        // An invite was accepted to a guild the application's bot is not in
        INVALID_INVITE_ACCEPT = 50036 ,
        // Invalid API version provided
        INVALID_API_VERSION = 50041 ,
        // File uploaded exceeds the maximum size
        FILE_SIZE_LIMIT = 50045 ,
        // Invalid file uploaded
        INVALID_FILE = 50046 ,
        // Cannot self-redeem this gift
        CANNOT_REDEEM = 50054 ,
        // Invalid Guild
        INVALID_GUILD = 50055 ,
        // Invalid message type
        INVALID_MESSAGE_TYPE = 50068 ,
        // Payment source required to redeem gift
        PAYMENT_SOURCE_REQUIRED = 50070 ,
        // Cannot delete a channel required for Community guilds
        CANNOT_DELETE_REQUIRED_CHANNEL = 50074 ,
        // Invalid sticker sent
        INVALID_STICKER = 50081 ,
        // Tried to perform an operation on an archived thread, such as editing a message or adding a user to the thread
        CANNOT_EXECUTE_THREAD_ARCHIVED = 50083 ,
        // Invalid thread notification settings
        INVALID_THREAD_NOTIFICATION_SETTINGS = 50084 ,
        // before value is earlier than the thread creation date  = 50085 ,
        // Community server channels must be text channels  = 50086 ,
        // This server is not available in your location  = 50095 ,
        // This server needs monetization enabled in order to perform this action  = 50097 ,
        // This server needs more boosts to perform this action  = 50101 ,
        // The request body contains invalid JSON.
        INVALID_JSON = 50109 ,
        // Two factor is required for this operation
        UNAUTHORIZED_2FACTOR_REQUIRED = 60003 ,
        // No users with DiscordTag exist  = 80004 ,
        // Reaction was blocked  = 90001 ,
        // API resource is currently overloaded. Try again a little later
        SERVER_ERROR_OVERLOAD_API = 130000 ,
        // The Stage is already open STAGE_ALREDY_OPEN = 150006 ,
        // Cannot reply without permission to read message history  = 160002 ,
        // A thread has already been created for this message  = 160004 ,
        // Thread is locked  = 160005 ,
        // Maximum number of active threads reached  = 160006 ,
        // Maximum number of active announcement threads reached  = 160007 ,
        // Invalid JSON for uploaded Lottie file
        INVALID_STICKER_LOTTIE = 170001 ,
        // Uploaded Lotties cannot contain rasterized images such as PNG or JPEG
        INVALID_STICKER_LOTTIE_IMAGE = 170002 ,
        // Sticker maximum framerate exceeded
        INVALID_STICKER_MAXIMUM_FRAMERATE = 170003 ,
        // Sticker frame count exceeds maximum of 1000 frames
        INVALID_STICKER_FRAME_COUNT_BOUNDS = 170004 ,
        // Lottie animation maximum dimensions exceeded
        INVALID_STICKER_LOTTIE_DIMENSIONS = 170005 ,
        // Sticker frame rate is either too small or too large
        INVALID_STICKER_FRAME_RATE_BOUNDS = 170006 ,
        // Sticker animation duration exceeds maximum of 5 seconds
        INVALID_STICKER_ANIMATION_DURATION_MAX = 170007 ,
        // Cannot update a finished event  = 180000 ,
        // Failed to create stage needed for stage event  = 180002 ,

    };
}