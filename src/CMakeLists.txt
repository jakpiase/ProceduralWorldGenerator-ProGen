set(BINARY ${CMAKE_PROJECT_NAME}_run)
set(LIBRARY ${CMAKE_PROJECT_NAME}_lib)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
list(REMOVE_ITEM SOURCES "main.cpp")
set(SOURCES ${SOURCES})

add_executable(${BINARY} main.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${LIBRARY} ${ZLIB_LIBRARIES})
target_link_libraries(${LIBRARY} SDL2)
target_link_libraries(${LIBRARY} glog)
target_link_libraries(${LIBRARY} EnTT)
target_link_libraries(${BINARY} ${LIBRARY})

file(COPY ${CMAKE_SOURCE_DIR}/src/python/infer.py
     DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/python/board_operations.py
     DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/python/ckpt-83.data-00000-of-00001
     DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/python/ckpt-83.index
     DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/python/valid_images.npy
     DESTINATION ${CMAKE_BINARY_DIR})