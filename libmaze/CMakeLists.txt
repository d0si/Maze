add_library(libmaze STATIC
    maze/element.h
    maze/array.h
    maze/object.h
    maze/type.h
    maze/helpers.h
    maze/element.cpp
    maze/array.cpp
    maze/object.cpp
    maze/type.cpp
    maze/helpers.cpp
)

target_include_directories(libmaze
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
