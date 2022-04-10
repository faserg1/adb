#include <libadb/api/sticker/sticker-api.hpp>
#include <libadb/api/context/context.hpp>
using namespace adb::api;

StickerApi::StickerApi(std::shared_ptr<Context> context) :
    context_(context)
{
    
}