add_executable(main main.cpp common.h chunk.h chunk.cpp memory.h memory.cpp debug.cpp debug.h value.h value.cpp vm.cpp vm.h)

target_link_libraries(main
    PRIVATE
    project_options
    project_warnings
    fmt::fmt
    docopt)