cmake_minimum_required(VERSION 3.16)
project(ProGen)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory(src)

add_executable(ProGen src/main.cpp)

target_link_libraries(ProGen Game)
target_link_libraries(ProGen Generator)
target_link_libraries(ProGen Algorithms)