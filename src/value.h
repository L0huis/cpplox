//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_VALUE_H
#define CPPLOX_VALUE_H

#include "common.h"

typedef double Value;

// NOTE: std::vector
struct ValueArray
{
    size_t capacity;
    size_t count;
    Value* values;
};

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif  //CPPLOX_VALUE_H
