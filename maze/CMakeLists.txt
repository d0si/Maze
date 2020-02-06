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
)
install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/maze
    DESTINATION include
)
