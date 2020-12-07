//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_COMPILER_H
#define CPPLOX_COMPILER_H

#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif  //CPPLOX_COMPILER_H
