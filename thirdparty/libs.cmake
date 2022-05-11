find_package(Threads REQUIRED)
if (!WIN32)
    find_package(loguru CONFIG REQUIRED)
endif(!WIN32)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)
# Here OpenSSL find_package need to be configured to ignore system paths
# On Windows system this could found not the right library (installed manually) and everything will blow up
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS random system)

find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")
find_path(LOGURU_INCLUDE_DIRS "loguru/loguru.cpp")

find_package(unofficial-sodium CONFIG REQUIRED)
find_package(Opus CONFIG REQUIRED)

set(THIRDPARTY_SOURCE
)

if (WIN32)
    list(APPEND THIRDPARTY_SOURCE
        ${LOGURU_INCLUDE_DIRS}/loguru/loguru.cpp
    )
endif (WIN32)

add_library(thirdparty_libs STATIC ${THIRDPARTY_SOURCE})