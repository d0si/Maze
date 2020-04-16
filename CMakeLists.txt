cmake_minimum_required(VERSION 3.10)
project(Maze
    LANGUAGES CXX
    VERSION 0.0.1
)

option(MAZE_BUILD_SHARED_LIBS "Build shared libs when enabled otherwise static" OFF)
option(MAZE_BUILD_TESTS "Build tests when enabled" ON)
option(MAZE_CODE_COVERAGE "Adds code coverage symbols" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Calculate CodeCoverage on GNU based compilers
if(MAZE_BUILD_TESTS AND MAZE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(Maze)

if(MAZE_BUILD_TESTS AND NOT WIN32)
enable_testing()
add_subdirectory(test)
endif()

#include(${CMAKE_SOURCE_DIR}/cmake/InstallConfig.cmake)
