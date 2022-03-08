#include <libadb/resource/locale.hpp>
#include <map>

using namespace adb::resource;

namespace
{
    std::map<Locale, std::pair<std::string, std::string>> localeMap
    {
        { Locale::EnglishUS, std::pair<std::string, std::string>("en-US", "English (United States)")},
        { Locale::EnglishGB, std::pair<std::string, std::string>("en-GB", "English (Great Britain)")},
        { Locale::Bulgarian, std::pair<std::string, std::string>("bg", "Bulgarian")},
        { Locale::ChineseChina, std::pair<std::string, std::string>("zh-CN", "Chinese (China)")},
        { Locale::ChineseTaiwan, std::pair<std::string, std::string>("zh-TW", "Chinese (Taiwan)")},
        { Locale::Croatian, std::pair<std::string, std::string>("hr", "Croatian")},
        { Locale::Czech, std::pair<std::string, std::string>("cs", "Czech")},
        { Locale::Danish, std::pair<std::string, std::string>("da", "Danish")},
        { Locale::Dutch, std::pair<std::string, std::string>("nl", "Dutch")},
        { Locale::Finnish, std::pair<std::string, std::string>("fi", "Finnish")},
        { Locale::French, std::pair<std::string, std::string>("fr", "French")},
        { Locale::German, std::pair<std::string, std::string>("de", "German")},
        { Locale::Greek, std::pair<std::string, std::string>("el", "Greek")},
        { Locale::Hindi, std::pair<std::string, std::string>("hi", "Hindi")},
        { Locale::Hungarian, std::pair<std::string, std::string>("hu", "Hungarian")},
        { Locale::Italian, std::pair<std::string, std::string>("it", "Italian")},
        { Locale::Japanese, std::pair<std::string, std::string>("ja", "Japanese")},
        { Locale::Korean, std::pair<std::string, std::string>("ko", "Korean")},
        { Locale::Lithuanian, std::pair<std::string, std::string>("lt", "Lithuanian")},
        { Locale::Norwegian, std::pair<std::string, std::string>("no", "Norwegian")},
        { Locale::Polish, std::pair<std::string, std::string>("pl", "Polish")},
        { Locale::PortugueseBrazil, std::pair<std::string, std::string>("pt-BR", "Portuguese (Brazil)")},
        { Locale::Romanian, std::pair<std::string, std::string>("ro", "Romanian")},
        { Locale::Russian, std::pair<std::string, std::string>("ru", "Russian")},
        { Locale::SpanishSpain, std::pair<std::string, std::string>("es-ES", "Spanish (Spain)")},
        { Locale::Swedish, std::pair<std::string, std::string>("sw-SE", "Swedish")},
        { Locale::Thai, std::pair<std::string, std::string>("th", "Thai")},
        { Locale::Turkish, std::pair<std::string, std::string>("tr", "Turkish")},
        { Locale::Ukrainian, std::pair<std::string, std::string>("uk", "Ukrainian")},
        { Locale::Vietnamese, std::pair<std::string, std::string>("vi", "Vietnamese")}
    };

    std::map<std::string, Locale> localeBackMap
    {
        { "en-US", Locale::EnglishUS },
        { "en-GB", Locale::EnglishGB },
        { "bg", Locale::Bulgarian },
        { "zh-CH", Locale::ChineseChina },
        { "zh-TW", Locale::ChineseTaiwan },
        { "hr", Locale::Croatian },
        { "cs", Locale::Czech },
        { "da", Locale::Danish },
        { "nl", Locale::Dutch },
        { "fi", Locale::Finnish },
        { "fr", Locale::French },
        { "de", Locale::German },
        { "el", Locale::Greek },
        { "hi", Locale::Hindi },
        { "hu", Locale::Hungarian },
        { "it", Locale::Italian },
        { "ja", Locale::Japanese },
        { "ko", Locale::Korean },
        { "lt", Locale::Lithuanian },
        { "no", Locale::Norwegian },
        { "pl", Locale::Polish },
        { "pt-BR", Locale::PortugueseBrazil },
        { "ro", Locale::Romanian },
        { "ru", Locale::Russian },
        { "es-ES", Locale::SpanishSpain },
        { "sw-SE", Locale::Swedish },
        { "th", Locale::Thai },
        { "tr", Locale::Turkish },
        { "uk", Locale::Ukrainian },
        { "vi", Locale::Vietnamese }
    };
}

void adb::resource::from_string(const std::string &str, Locale &locale)
{
    locale = localeBackMap.find(str)->second;
}

std::string adb::resource::to_string(Locale locale)
{
    return localeMap.find(locale)->second.first;
}

std::string adb::resource::to_display_name(Locale locale)
{
    return localeMap.find(locale)->second.second;
}