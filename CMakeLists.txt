cmake_minimum_required(VERSION 3.13)
project(Maze
    LANGUAGES CXX
    VERSION 1.2.0
)


#
# Project build configuration options
#
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # This allows new policy to override option variables using normal variables
cmake_policy(SET CMP0077 NEW) # This allows new policy to override option variables using normal variables
option(MAZE_BUILD_SHARED_LIBS "Build shared libs when enabled otherwise static" ON)
option(MAZE_BUILD_TESTS "Build tests when enabled" ON)
option(MAZE_CODE_COVERAGE "Adds code coverage symbols" OFF)


#
# Global build settings
#
# If configuration was not set in CMAKE_BUILD_TYPE default to Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type: Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
    # Add possible build types
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build libraries and executables into same directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#
# Include solution projects
#
add_subdirectory(src)
if(MAZE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
