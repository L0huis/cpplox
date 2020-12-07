//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_CHUNK_H
#define CPPLOX_CHUNK_H

#include "common.h"
#include "value.h"

enum OpCode
{
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE,
    OP_RETURN,
};

// NOTE: Basically a std::vector
struct Chunk
{
    size_t     count;
    size_t     capacity;
    uint8_t*   code;
    int*       lines;
    ValueArray constants;
};

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int  addConstant(Chunk* chunk, Value value);

#endif  //CPPLOX_CHUNK_H
