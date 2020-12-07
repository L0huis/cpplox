//
// Created by julianlohuis on 05/12/2020.
//

#ifndef CPPLOX_VALUE_H
#define CPPLOX_VALUE_H

#include "common.h"

struct Obj;
struct ObjString;

enum ValueType
{
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ
};

struct Value
{
    ValueType type;
    union
    {
        bool   boolean;
        double number;
        Obj*   obj;
    } as;
};

#define IS_BOOL(value)   ((value).type == VAL_BOOL)
#define IS_NIL(value)    ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define IS_OBJ(value)    ((value).type == VAL_OBJ)

#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value)   (Value{VAL_BOOL, {.boolean = value}})
#define NIL_VAL           (Value{VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) (Value{VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object)   (Value{VAL_OBJ, {.obj = (Obj*)object}})

// NOTE: std::vector
struct ValueArray
{
    size_t capacity;
    size_t count;
    Value* values;
};

bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif  //CPPLOX_VALUE_H
