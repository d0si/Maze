add_library(maze STATIC
    src/maze/element.cpp
    src/maze/array.cpp
    src/maze/object.cpp
    src/maze/type.cpp
    src/maze/helpers.cpp
    src/maze/config.cpp
)

configure_file(src/maze/config.hpp.in src/maze/config.hpp)

target_include_directories(maze
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}/maze/src
        ${PROJECT_SOURCE_DIR}/thirdparty/nlohmann/json/include
)

install(TARGETS maze
    DESTINATION lib
    EXPORT mazeTargets
)
install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/maze
    DESTINATION include
)
install(
    EXPORT mazeTargets
    FILE mazeTargets.cmake
    DESTINATION lib/cmake/maze
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/mazeConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/maze"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mazeConfigVersion.cmake"
    VERSION "${maze_VERSION_MAJOR}.${maze_VERSION_MINOR}.${maze_VERSION_PATCH}"
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/mazeConfig.cmake
    DESTINATION lib/cmake/maze
)
export(EXPORT mazeTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/mazeTargets.cmake"
)
