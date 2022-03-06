set(ROOT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_SRC_DIR ${ROOT_LIB_DIR}/src)
set(ROOT_INCLUDE_DIR ${ROOT_LIB_DIR}/include)
file(GLOB_RECURSE LIBADB_SOURCES *.cpp *.hpp *.h)

add_library(libadb SHARED ${LIBADB_SOURCES})
set_property(TARGET libadb PROPERTY CXX_STANDARD_REQUIRED 20)

target_compile_definitions(libadb PRIVATE LIBADB_EXPORTS)

target_include_directories(libadb PRIVATE
    ${USOCKETS_INCLUDE_DIRS}
    ${UWEBSOCKETS_INCLUDE_DIRS}
)

target_include_directories(libadb PUBLIC
    ${ROOT_INCLUDE_DIR}
)

target_include_directories(libadb PRIVATE
    ${ROOT_SRC_DIR}
)

target_link_libraries(libadb PRIVATE date::date date::date-tz)
target_link_libraries(libadb PRIVATE Boost::boost Boost::system Boost::random)
target_link_libraries(libadb PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(libadb PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(libadb PRIVATE fmt::fmt)
target_link_libraries(libadb PRIVATE cpr::cpr)

target_link_libraries(libadb PRIVATE toml11::toml11)
target_link_libraries(libadb PRIVATE websocketpp::websocketpp)

target_link_libraries(libadb PRIVATE unofficial-sodium::sodium)
target_link_libraries(libadb PRIVATE Opus::opus)

target_link_libraries(libadb PRIVATE ${USOCKETS_LIBRARY})

target_secrets(libadb)
