cmake_minimum_required(VERSION 3.12)

# Uncomment to search encounted problems
# set(BUILD_VERBOSE TRUE)

# Paths
set(ADB_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ADB_THIRDPARTY_DIR ${ADB_ROOT_DIR}/thirdparty)

include(${ADB_ROOT_DIR}/cmake/toolchain.cmake)

project(adb CXX)

include(${ADB_ROOT_DIR}/cmake/arch.cmake)
include(${ADB_ROOT_DIR}/cmake/secrets.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

# Thirdparty librariies
include(${ADB_THIRDPARTY_DIR}/libs.cmake)

add_subdirectory(src)