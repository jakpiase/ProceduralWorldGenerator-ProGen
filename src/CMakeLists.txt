set(BINARY ${CMAKE_PROJECT_NAME}_run)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
list(REMOVE_ITEM SOURCES "main.cpp")
set(SOURCES ${SOURCES})

add_executable(${BINARY} main.cpp)
#target_link_libraries(glog STATIC ${SOURCES})

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_lib glog)
target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib)
