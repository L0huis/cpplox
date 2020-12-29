#ifndef clox_compiler_h
#define clox_compiler_h

#include <string_view>

#include "object.h"
#include "vm.h"

ObjFunction* compile(std::string_view source);
void         markCompilerRoots();

#endif
