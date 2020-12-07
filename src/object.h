//
// Created by julianlohuis on 07/12/2020.
//

#ifndef CPPLOX_OBJECT_H
#define CPPLOX_OBJECT_H

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)  (AS_OBJ(value)->type)
#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value)  ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ(value))->chars)

enum ObjType
{
    OBJ_STRING,
};

struct Obj
{
    ObjType type;
    Obj* next;
};

struct ObjString
{
    Obj   obj;
    int   length;
    char* chars;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void       printObject(Value value);

static inline bool isObjType(Value value, ObjType type)
{
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif  //CPPLOX_OBJECT_H
