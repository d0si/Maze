add_library(libmaze STATIC
    maze/element.cpp
    maze/array.cpp
    maze/object.cpp
    maze/type.cpp
    maze/helpers.cpp
)

target_include_directories(libmaze
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
#        ${CMAKE_CURRENT_SOURCE_DIR}
)
