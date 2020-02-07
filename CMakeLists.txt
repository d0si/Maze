cmake_minimum_required(VERSION 3.10)
project(maze
    LANGUAGES CXX
    VERSION 0.0.1
)

option(MAZE_BUILD_TESTS "Build tests when enabled" ON)
option(MAZE_INSTALL "Install targets during install step" ON)
option(MAZE_CODE_COVERAGE "Adds code coverage symbols" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Calculate CodeCoverage on GNU based compilers
if(MAZE_BUILD_TESTS AND MAZE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(maze)

if(MAZE_BUILD_TESTS)
enable_testing()
add_subdirectory(test)
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${maze_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${maze_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${maze_VERSION_PATCH}")
include(CPack)
