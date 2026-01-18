cmake_minimum_required(VERSION 4.1)
set(EXECUTABLE_NAME "run")
set(PROJECTNAME "engine")

Project("${PROJECTNAME}")
add_executable("${EXECUTABLE_NAME}"  engine.cpp engine/src/board/board.cpp)

target_include_directories(
  "${EXECUTABLE_NAME}"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/engine/src/"
)
