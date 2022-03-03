find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(toml11 CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)
# Here OpenSSL find_package need to be configured to ignore system paths
# On Windows system this could found not the right library (installed manually) and everything will blow up
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS random system)

find_path(USOCKETS_INCLUDE_DIRS "libusockets.h")
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")

find_library(USOCKETS_LIBRARY NAMES uSockets REQUIRED)

find_package(unofficial-sodium CONFIG REQUIRED)
find_package(Opus CONFIG REQUIRED)