#pragma once

#include <string>
#include <memory>

namespace adb::api
{
    class Context;
    class DiscordApi;

    class StickerApi
    {
        friend DiscordApi;
    private:
        StickerApi(std::shared_ptr<Context> context);
    private:
        std::shared_ptr<Context> context_;
    };
}