#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

enum OpCode
{
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_POP,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_GET_GLOBAL,
    OP_DEFINE_GLOBAL,
    OP_SET_GLOBAL,
    OP_GET_UPVALUE,
    OP_SET_UPVALUE,
    OP_GET_PROPERTY,
    OP_SET_PROPERTY,
    OP_GET_SUPER,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE,
    OP_PRINT,
    OP_JUMP,
    OP_JUMP_IF_FALSE,
    OP_LOOP,
    OP_CALL,
    OP_INVOKE,
    OP_SUPER_INVOKE,
    OP_CLOSURE,
    OP_CLOSE_UPVALUE,
    OP_RETURN,
    OP_CLASS,
    OP_INHERIT,
    OP_METHOD
};

class Chunk
{
private:
    std::vector<uint8_t> m_code{};
    std::vector<int>     m_lines{};
    ValueArray           m_constants{};

public:
    Chunk() = default;

    void              writeChunk(uint8_t byte, int line);
    [[nodiscard]] int addConstant(Value value);

    [[nodiscard]] size_t size() const noexcept;

    [[nodiscard]] std::vector<uint8_t>& code() noexcept;
    [[nodiscard]] std::vector<int>&     lines() noexcept;
    [[nodiscard]] ValueArray&           constants() noexcept;
};

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);

#endif
