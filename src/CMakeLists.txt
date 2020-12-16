#
# Include project file list variables
#
include(Maze.cmake)


#
# Add library
#
if(MAZE_BUILD_SHARED_LIBS)
    set(MAZE_LIBRARY_TYPE SHARED)
else()
    set(MAZE_LIBRARY_TYPE STATIC)
endif()

add_library(${PROJECT_NAME} ${MAZE_LIBRARY_TYPE} ${MAZE_SOURCES} ${MAZE_PUBLIC_HEADERS})
add_library(Maze::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC MAZE_EXPORTS)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/nlohmann/json/include
)

# Set library version information
set_target_properties(Maze PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Maze PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Configure version file
configure_file(../include/Maze/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/Maze/Version.hpp" @ONLY
)
set(MAZE_PUBLIC_HEADERS
    ${MAZE_PUBLIC_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/include/Maze/Version.hpp"
)
