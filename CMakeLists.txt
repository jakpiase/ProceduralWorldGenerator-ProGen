cmake_minimum_required(VERSION 3.16)
project(ProGen)
set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory(progen)

add_executable(ProGenMain progen/main.cpp)

target_link_libraries(ProGenMain Game)
target_link_libraries(ProGenMain Generator)
target_link_libraries(ProGenMain Algorithms)
