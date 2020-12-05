add_executable(main main.cpp common.h chunk.h chunk.cpp memory.h memory.cpp debug.cpp debug.h value.h value.cpp)

target_link_libraries(main
    PRIVATE
    project_options
    project_warnings
    fmt::fmt
    docopt)