#pragma once

#define ADB_ENUM_FLAGS_OPERATORS(ENUM_NAME, FLAGS_NAME, ENUM_BASE) \
using FLAGS_NAME = ENUM_BASE;\
\
constexpr FLAGS_NAME operator+(ENUM_NAME e)\
{\
    return static_cast<ENUM_BASE>(e);\
}\
\
constexpr FLAGS_NAME operator|(ENUM_NAME e1, ENUM_NAME e2)\
{\
    return static_cast<ENUM_BASE>(e1) | static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator|(FLAGS_NAME e1, ENUM_NAME e2)\
{\
    return e1 | static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator&(ENUM_NAME e1, ENUM_NAME e2)\
{\
    return static_cast<ENUM_BASE>(e1) & static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator&(FLAGS_NAME e1, ENUM_NAME e2)\
{\
    return e1 & static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator|=(ENUM_NAME e1, ENUM_NAME e2)\
{\
    return static_cast<ENUM_BASE>(e1) | static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator|=(FLAGS_NAME e1, ENUM_NAME e2)\
{\
    return e1 | static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator&=(ENUM_NAME e1, ENUM_NAME e2)\
{\
    return static_cast<ENUM_BASE>(e1) & static_cast<ENUM_BASE>(e2);\
}\
\
constexpr FLAGS_NAME operator&=(FLAGS_NAME e1, ENUM_NAME e2)\
{\
    return e1 & static_cast<ENUM_BASE>(e2);\
}
