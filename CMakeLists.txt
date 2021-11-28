cmake_minimum_required(VERSION 3.16)
project(ProGen)
set(CMAKE_CXX_STANDARD 20)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG release-1.11.0
    OPTIONS -DBUILD_TESTING=OFF
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

CPMAddPackage(
    NAME EnTT
    GITHUB_REPOSITORY skypjack/entt
    VERSION 3.8.1
    OPTIONS -DBUILD_TESTING=OFF
)

if(WIN32)
    add_definitions(-DHAVE_SNPRINTF)
endif(WIN32)

CPMAddPackage(
    NAME glog
    GITHUB_REPOSITORY google/glog
    VERSION 0.5.0
    OPTIONS -DBUILD_TESTING=OFF
)

CPMAddPackage(
        NAME SDL2
        URL https://www.libsdl.org/release/SDL2-2.0.16.zip
)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SOURCE_DIR src)
set(DEPENDENCIES_DIR deps)
set(TEST_DIR tests)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(${DEPENDENCIES_DIR})
add_subdirectory(${SOURCE_DIR})
add_subdirectory(${TEST_DIR})
