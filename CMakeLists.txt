cmake_minimum_required(VERSION 3.10)
project(maze CXX)

# Calculate CodeCoverage on GNU based compilers
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
