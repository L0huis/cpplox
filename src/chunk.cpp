#include <cstdlib>

#include "chunk.h"
#include "memory.h"
#include "vm.h"

void initChunk(Chunk* chunk)
{
    std::construct_at(chunk);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk)
{
    std::destroy_at(chunk);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    chunk->code.push_back(byte);
    chunk->lines.push_back(line);
}

int addConstant(Chunk* chunk, Value value)
{
    push(value);
    writeValueArray(&chunk->constants, value);
    pop();
    return chunk->constants.values.size() - 1;
}
