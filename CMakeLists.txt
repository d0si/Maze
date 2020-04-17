cmake_minimum_required(VERSION 3.10)
project(Maze
    LANGUAGES CXX
    VERSION 0.0.1
)


#
# Build configuration options
#
option(MAZE_BUILD_SHARED_LIBS "Build shared libs when enabled otherwise static" OFF)
option(MAZE_BUILD_TESTS "Build tests when enabled" ON)
option(MAZE_CODE_COVERAGE "Adds code coverage symbols" OFF)


#
# Compiler flags
#
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Calculate CodeCoverage on GNU based compilers
if(MAZE_BUILD_TESTS AND MAZE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()


#
# Maze library
#
set(MAZE_SOURCES
    Maze/Element.cpp
    Maze/Object.cpp
    Maze/Array.cpp
    Maze/Type.cpp
    Maze/Helpers.cpp
    Maze/Version.cpp
)
set(MAZE_PUBLIC_HEADERS
    Maze/Element.hpp
    Maze/Object.hpp
    Maze/Array.hpp
    Maze/Type.hpp
    Maze/Helpers.hpp
)

# If configuration was not set in CMAKE_BUILD_TYPE default to Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type: Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
    # Add possible build types
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif()

# Library output type
if(MAZE_BUILD_SHARED_LIBS)
    set(MAZE_LIBRARY_TYPE SHARED)
else()
    set(MAZE_LIBRARY_TYPE STATIC)
endif()

# Add target library
add_library(Maze ${MAZE_LIBRARY_TYPE}
    ${MAZE_SOURCES}
    ${MAZE_PUBLIC_HEADERS}
)

target_include_directories(Maze
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nlohmann/json/include
)

# Set library version information
set_target_properties(Maze PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Maze PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Configure version file
configure_file(Maze/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/Maze/Version.hpp" @ONLY
)
set(MAZE_PUBLIC_HEADERS
    ${MAZE_PUBLIC_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/Maze/Version.hpp"
)


#
# Unit testing
#
if(MAZE_BUILD_TESTS)
    enable_testing()
    
    set(INSTALL_GTEST OFF)
    set(gtest_force_shared_crt ON)
    add_subdirectory(dependencies/googletest)

    set(MAZE_TEST_SOURCES
        MazeTest/ArrayTest.cpp
        MazeTest/main.cpp
    )

    add_executable(MazeTest
        ${MAZE_TEST_SOURCES}
    )

    add_test(NAME MazeTest COMMAND MazeTest)

    target_link_libraries(MazeTest
        PUBLIC
            Maze
            gtest
    )
endif()
