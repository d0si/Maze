#
# Unit testing
#
enable_testing()
    
set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)


#
# Include project file list variables
#
include(Tests.cmake)


#
# Add unit tests executable
#
add_executable(Maze_tests
    ${MAZE_TESTS_SOURCES}
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
            COMMAND ${CMAKE_SOURCE_DIR}/dependencies/fastcov/fastcov.py --lcov -o maze_test_coverage.info --include include/Maze/Maze/
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
