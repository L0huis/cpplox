//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_VM_H
#define CPPLOX_VM_H

#include "object.h"
#include "table.h"
#include "chunk.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX  (FRAMES_MAX * UINT8_COUNT)

struct CallFrame
{
    ObjClosure* closure;
    uint8_t*    ip;
    Value*      slots;
};

struct VM
{
    CallFrame frames[FRAMES_MAX];
    int       frameCount;

    Value       stack[STACK_MAX];
    Value*      stackTop;
    Table       globals;
    Table       strings;
    ObjUpvalue* openUpvalues;

    Obj* objects;
};

enum InterpretResult
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

extern VM vm;

void            initVM();
void            freeVM();
InterpretResult interpret(const char* source);
void            push(Value value);
Value           pop();

#endif  //CPPLOX_VM_H
