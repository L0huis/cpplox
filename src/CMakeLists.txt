add_executable(main main.cpp Lox.cpp Lox.h TokenType.h Token.cpp Token.h Scanner.cpp Scanner.h TokenType.cpp)

target_link_libraries(main
    PRIVATE
    project_options
    project_warnings
    fmt::fmt
    docopt)