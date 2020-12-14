cmake_minimum_required(VERSION 3.13)
project(Maze
    LANGUAGES CXX
    VERSION 1.1.0
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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#
# Maze library sources
#
set(MAZE_SOURCES
    Maze/Element.cpp
    Maze/Type.cpp
    Maze/Helpers.cpp
    Maze/Version.cpp
    Maze/MazeException.cpp
)
set(MAZE_PUBLIC_HEADERS
    Maze/Maze.hpp
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
add_library(Maze::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


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
        tests/ElementTest.cpp
        tests/ArrayTest.cpp
        tests/ObjectTest.cpp
        tests/TypeTest.cpp
        tests/HelpersTest.cpp

        tests/Element/Bool.cpp

        tests/main.cpp
    )

    add_executable(Maze_tests
        ${MAZE_TEST_SOURCES}
    )

    add_test(NAME Maze_tests COMMAND Maze_tests)

    target_link_libraries(Maze_tests
        PUBLIC
            Maze
            gtest
    )

    # Calculate CodeCoverage on GNU based compilers
    if(MAZE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage  -fprofile-arcs -ftest-coverage")
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage  -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 9.0)
            add_custom_target(Maze_tests_coverage
                COMMAND Maze_tests ${ARGV3}
                COMMAND ${CMAKE_SOURCE_DIR}/cmake/fastcov/fastcov.py --lcov -o maze_test_coverage.info --include Maze/Maze/
                COMMAND genhtml -o coverage_info maze_test_coverage.info
            )
        else()
            add_custom_target(Maze_tests_coverage
                COMMAND lcov --zerocounters --directory .
                COMMAND Maze_tests ${ARGV3}
                COMMAND lcov --capture --directory . --output-file maze_test_coverage.info
                COMMAND genhtml -o coverage_info maze_test_coverage.info
            )
        endif()

    endif()
endif()
