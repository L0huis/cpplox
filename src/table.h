//
// Created by julianlohuis on 07/12/2020.
//

#ifndef CPPLOX_TABLE_H
#define CPPLOX_TABLE_H

#include "common.h"
#include "value.h"

struct Entry
{
    ObjString* key;
    Value      value;
};

struct Table
{
    int    count;
    int    capacity;
    Entry* entries;
};

void       initTable(Table* table);
void       freeTable(Table* table);
bool       tableGet(Table* table, ObjString* key, Value* value);
bool       tableSet(Table* table, ObjString* key, Value value);
bool       tableDelete(Table* table, ObjString* key);
void       tableAddAll(Table* from, Table* to);
ObjString* tableFindString(Table* table, const char* chars, int length, uint32_t hash);

#endif  //CPPLOX_TABLE_H
