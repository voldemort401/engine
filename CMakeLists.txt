cmake_minimum_required(VERSION 4.1)

set(EXECUTABLE_NAME "run")
set(PROJECTNAME "engine")

project("${PROJECTNAME}")

add_executable("${EXECUTABLE_NAME}" 
    engine.cpp 
    engine/src/board/board.cpp)

target_include_directories("${EXECUTABLE_NAME}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/engine/src/"
)

add_custom_target(debug
    COMMAND $<TARGET_FILE:${EXECUTABLE_NAME}>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building in debug mode with -g flag"
)
