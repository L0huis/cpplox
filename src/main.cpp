#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl()
{
    std::string line;
    for (;;)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line))
        {
            std::cout << '\n';
            break;
        }
        interpret(line);
    }
}
static std::string readFile(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    file.seekg(0L, std::ios::end);
    auto size = file.tellg();
    file.seekg(0L, std::ios::beg);

    std::string buffer(size, '\0');

    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), buffer.begin());

    return buffer;
}
static void runFile(const char* path)
{
    std::string     source = readFile(path);
    InterpretResult result = interpret(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[])
{
    initVM();

    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    freeVM();
    return 0;
}
