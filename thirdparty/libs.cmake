find_package(Threads REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)
# Here OpenSSL find_package need to be configured to ignore system paths
# On Windows system this could found not the right library (installed manually) and everything will blow up
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS random system)

find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")

find_package(unofficial-sodium CONFIG REQUIRED)
find_package(Opus CONFIG REQUIRED)