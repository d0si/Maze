cmake_minimum_required(VERSION 3.10)
project(demo_project
    LANGUAGES CXX
)

find_package(maze REQUIRED)

add_executable(demo_project
    main.cpp
)

target_link_libraries(demo_project
    PRIVATE maze
)
