#pragma once

#ifdef _WIN32
#    ifdef LIBADB_EXPORTS
#        define LIBADB_API __declspec(dllexport)
#    else
#        define LIBADB_API __declspec(dllimport)
#    endif
#elif
#    define LIBADB_API
#endif