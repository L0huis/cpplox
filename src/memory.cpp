//
// Created by julianlohuis on 05/12/2020.
//
#include <cstdlib>

#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return nullptr;
    }

    void* result = realloc(pointer, newSize);
    if (result == nullptr) exit(1);
    return result;
}
