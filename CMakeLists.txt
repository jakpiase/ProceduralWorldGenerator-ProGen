cmake_minimum_required(VERSION 3.16)
project(ProGen)
set(CMAKE_CXX_STANDARD 20)

include(cmake/CPM.cmake)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

CPMAddPackage(
    NAME glog
    GITHUB_REPOSITORY google/glog
    VERSION 0.5.0)

set(SOURCE_DIR src)
set(TEST_DIR tests)

include_directories(${SOURCE_DIR})

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${TEST_DIR})
