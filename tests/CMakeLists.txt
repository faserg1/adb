set(ROOT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE TESTADB_SOURCES *.cpp *.hpp *.h)

add_executable(testadb ${TESTADB_SOURCES})
set_property(TARGET testadb PROPERTY CXX_STANDARD_REQUIRED 20)

target_link_libraries(testadb PRIVATE libadb)
target_link_libraries(testadb PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(testadb PRIVATE fmt::fmt)
target_link_libraries(testadb PRIVATE Threads::Threads)