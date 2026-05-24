#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// the \ tell the macro to keep reading the next line
// 8 is a minimum threshold, could tweak that depend on the real case scenario
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
(type*)reallocate(pointer,sizeof(type)*(oldCount),\
    sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount)\
reallocate(pointer, sizeof(type)* oldCount,0)

// The reallocate() function is the singlest function for dynamic mem
// management
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif
