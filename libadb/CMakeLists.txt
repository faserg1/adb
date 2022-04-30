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
    ${HFSM2_INCLUDE_DIRS}
)

target_include_directories(libadb PUBLIC
    "$<BUILD_INTERFACE:${ROOT_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
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
target_link_libraries(libadb PRIVATE websocketpp::websocketpp)

target_link_libraries(libadb PRIVATE unofficial-sodium::sodium)
target_link_libraries(libadb PRIVATE Opus::opus)

target_link_libraries(libadb PRIVATE ${USOCKETS_LIBRARY})

set(ADB_PROJECT_CONFIG ${PROJECT_BINARY_DIR}/adb-config.cmake)

set(targets_export_name libadb-targets)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/adb-config.cmake.in
    ${ADB_PROJECT_CONFIG}
    INSTALL_DESTINATION ${ADB_CMAKE_OUT})

install(
    FILES ${ADB_PROJECT_CONFIG}
    DESTINATION ${ADB_CMAKE_OUT})
install(TARGETS libadb EXPORT ${targets_export_name})
install(DIRECTORY "include/libadb" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT libadb-targets
    NAMESPACE libadb::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/libadb)