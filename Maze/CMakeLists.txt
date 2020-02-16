# Set cpp sources
set(MAZE_SOURCES
    src/Maze/Array.cpp
    src/Maze/Version.cpp
    src/Maze/Element.cpp
    src/Maze/Object.cpp
    src/Maze/Type.cpp
    src/Maze/Helpers.cpp
)

# Set headers
set(MAZE_HEADERS
    include/Maze/Array.hpp
    include/Maze/Element.hpp
    include/Maze/Helpers.hpp
    include/Maze/Maze.hpp
    include/Maze/Object.hpp
    include/Maze/Type.hpp
)

# Fallback to Release build if nothing else was chosen
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type will be 'Release'.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

  # Add possible build types
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Select library output type
if(MAZE_BUILD_SHARED_LIBS)
    set(MAZE_LIBRARY_TYPE SHARED)
else()
    set(MAZE_LIBRARY_TYPE STATIC)
endif()

# Add target library
add_library(maze ${MAZE_LIBRARY_TYPE}
    ${MAZE_SOURCES}
    ${MAZE_HEADERS}
)

# Add include directories
target_include_directories(maze
    INTERFACE
         $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}/Maze
        ${PROJECT_SOURCE_DIR}/thirdparty/nlohmann/json/include
)

# Install library
install(TARGETS maze
    EXPORT MazeExport
    RUNTIME DESTINATION "bin" COMPONENT bin
    LIBRARY DESTINATION "lib" COMPONENT shlib
    ARCHIVE DESTINATION "lib" COMPONENT stlib
    COMPONENT dev
)

# Create Maze/Version.hpp
configure_file(src/Maze/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/Maze/Version.hpp" @ONLY
)
set(MAZE_HEADERS
    ${MAZE_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/Maze/Version.hpp"
)

# Install header files
install(FILES ${MAZE_HEADERS}
    DESTINATION "include/Maze"
)
