//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_DEBUG_H
#define CPPLOX_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int  disassembleInstruction(Chunk* chunk, int offset);

#endif  //CPPLOX_DEBUG_H
