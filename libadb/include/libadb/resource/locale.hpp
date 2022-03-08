#pragma once

#include <libadb/libadb.hpp>
#include <string>

namespace adb::resource
{
    /**
     * @brief Locale
     * @details https://discord.com/developers/docs/reference#locales
     */
    enum class Locale
    {
        /// English (United States), en-US
        EnglishUS,
        /// English (Great Britain), en-GB
        EnglishGB,
        /// Bulgarian, bg
        Bulgarian,
        /// Chinese (China), zh-CN
        ChineseChina,
        /// Chinese (Taiwan), zh-TW
        ChineseTaiwan,
        /// Croatian, hr
        Croatian,
        /// Czech, cs
        Czech,
        /// Danish, da
        Danish,
        /// Dutch, nl
        Dutch,
        /// Finnish, fi
        Finnish,
        /// French, fr
        French,
        /// German, de
        German,
        /// Greek, el
        Greek,
        /// Hindi, hi
        Hindi,
        /// Hungarian, hu
        Hungarian,
        /// Italian, it
        Italian,
        /// Japanese, ja
        Japanese,
        /// Korean, ko
        Korean,
        /// Lithuanian, lt
        Lithuanian,
        /// Norwegian, no
        Norwegian,
        /// Polish, pl
        Polish,
        /// Portuguese (Brazil), pt-BR
        PortugueseBrazil,
        /// Romanian, ro
        Romanian,
        /// Russian, ru
        Russian,
        /// Spanish (Spain), es-ES
        SpanishSpain,
        /// Swedish, sv-SE
        Swedish,
        /// Thai, th
        Thai,
        /// Turkish, tr
        Turkish,
        /// Ukrainian, uk
        Ukrainian,
        /// Vietnamese, vi
        Vietnamese,
    };

    LIBADB_API void from_string(const std::string &str, Locale &locale);
    LIBADB_API std::string to_string(Locale locale);

    LIBADB_API std::string to_display_name(Locale locale);
}