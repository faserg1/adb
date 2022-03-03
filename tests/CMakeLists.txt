set(ROOT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE TESTADB_SOURCES *.cpp *.hpp *.h)

add_executable(testadb ${TESTADB_SOURCES})
target_link_libraries(testadb PRIVATE libadb)

target_link_libraries(testadb PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(testadb PRIVATE fmt::fmt)