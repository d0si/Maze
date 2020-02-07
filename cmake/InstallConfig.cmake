# INSTALL_CMAKE_DIR
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/Maze)
endif()

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR}
    CACHE PATH "Relative instalation path for CMake files"
)
set(CMAKE_INSTALL_RPATH lib)

install(EXPORT MazeExport
    DESTINATION ${INSTALL_CMAKE_DIR}
    FILE MazeTargets.cmake
)

# MazeConfig.cmake.in
configure_file(${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MazeConfig.cmake" @ONLY
)

# MazeConfigVersion.cmake.in
configure_file(${CMAKE_SOURCE_DIR}/cmake/ConfigVersion.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MazeConfigVersion.cmake" @ONLY
)

# Install MazeConfig.cmake and MazeConfigVersion.cmake
install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MazeConfig.cmake"
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MazeConfigVersion.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev
)

# Create uninstall target
configure_file("${CMAKE_SOURCE_DIR}/cmake/Uninstall.cmake.in"
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Uninstall.cmake" IMMEDIATE @ONLY
)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Uninstall.cmake
)
