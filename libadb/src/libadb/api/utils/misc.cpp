#include <libadb/api/utils/misc.hpp>

namespace adb::api
{
    // Гордо скомунизжено со StackOverflow
    std::string getOsName()
    {
        #if defined(_WIN32) || defined(_WIN64)
        // Надеюсь, только в целях отладки и тестирования.
        return "Windows";
        #elif __APPLE__ || __MACH__
        // Только попробуй на нем запустить. Я тебя съем. Заживо.
        return "Mac OSX";
        #elif __linux__
        return "Linux";
        #elif __FreeBSD__
        return "FreeBSD";
        #elif __unix || __unix__
        return "Unix";
        #else
        return "Unknown";
        #endif
    }
}