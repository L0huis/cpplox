add_library(cpplox STATIC common.h chunk.h chunk.cpp memory.h memory.cpp debug.cpp debug.h value.h value.cpp vm.cpp vm.h compiler.cpp compiler.h scanner.cpp scanner.h object.h object.cpp table.cpp table.h constexpr_map.h)

target_link_libraries(cpplox
    project_options
    project_warnings
    fmt::fmt)

add_executable(main main.cpp)

target_link_libraries(main
    PRIVATE
    cpplox
    project_options
    project_warnings
    fmt::fmt
    docopt)