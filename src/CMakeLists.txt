set(ROOT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE ADB_SOURCES *.cpp *.hpp *.h)

add_executable(adb ${ADB_SOURCES})
set_property(TARGET adb PROPERTY CXX_STANDARD_REQUIRED 20)

target_include_directories(adb PRIVATE
    ${USOCKETS_INCLUDE_DIRS}
    ${UWEBSOCKETS_INCLUDE_DIRS}
)

target_include_directories(adb PRIVATE
    ${ROOT_SRC_DIR}
)

target_link_libraries(adb PRIVATE date::date date::date-tz)
target_link_libraries(adb PRIVATE Boost::boost Boost::system Boost::random)
target_link_libraries(adb PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(adb PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(adb PRIVATE fmt::fmt)
target_link_libraries(adb PRIVATE cpr::cpr)
target_link_libraries(adb PRIVATE toml11::toml11)
target_link_libraries(adb PRIVATE websocketpp::websocketpp)

target_link_libraries(adb PRIVATE ${USOCKETS_LIBRARY})

target_secrets(adb)
