cmake_minimum_required(VERSION 3.10)
project(demo_project
    LANGUAGES CXX
)

find_package(Maze REQUIRED)

add_executable(demo_project
    main.cpp
)

target_include_directories(demo_project
    PRIVATE
        ${MAZE_INCLUDE_DIRS}
)

target_link_libraries(demo_project
    PRIVATE
        ${MAZE_LIBRARIES}
)
