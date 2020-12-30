#include <cstdlib>

#include "chunk.h"
#include "memory.h"
#include "vm.h"

void initChunk(Chunk* chunk)
{
    std::construct_at(chunk);
}

void freeChunk(Chunk* chunk)
{
    std::destroy_at(chunk);
}

void Chunk::writeChunk(uint8_t byte, int line) noexcept
{
    m_code.push_back(byte);
    m_lines.push_back(line);
}

int Chunk::addConstant(Value value) noexcept
{
    push(value);
    m_constants.push_back(value);
    pop();
    return m_constants.size() - 1;
}

size_t Chunk::size() const noexcept
{
    return m_code.size();
}

std::vector<uint8_t>& Chunk::code() noexcept
{
    return m_code;
}

std::vector<int>& Chunk::lines() noexcept
{
    return m_lines;
}

ValueArray& Chunk::constants() noexcept
{
    return m_constants;
}
