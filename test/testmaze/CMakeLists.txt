set(CMAKE_CXX_STANDARD 11)

if(WIN32)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrtd")
endif()

add_executable(testmaze
    arraytest.cpp
    main.cpp
)

target_link_libraries(testmaze
    maze
    libgtest
    libgmock
)

add_test(NAME testmaze
    COMMAND testmaze
)
