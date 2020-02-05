find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(gtest
    URL https://github.com/google/googletest/archive/release-1.10.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable installation command
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest
    source_dir
    binary_dir
)

add_library(libgtest
    IMPORTED STATIC GLOBAL
)
add_dependencies(libgtest
    gtest
)

if(WIN32)
set_target_properties(libgtest
    PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gtestd.lib"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
else()
set_target_properties(libgtest
    PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif(WIN32)


add_library(libgmock
    IMPORTED STATIC GLOBAL
)
add_dependencies(libgmock
    gtest
)

if (WIN32)
set_target_properties(libgmock
    PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gmockd.lib"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
else()
set_target_properties(libgmock
    PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif(WIN32)

include_directories(
    "${source_dir}/googletest/include"
    "${source_dir}/googlemock/include"
)

add_subdirectory(testmaze)
