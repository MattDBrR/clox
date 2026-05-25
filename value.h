#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;


// Implementation of constant pool
// Sequence of double
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;


// Constructor
void initValueArray(ValueArray* array);
// Update
void writeValueArray(ValueArray* array, Value value);
// Free
void freeValueArray(ValueArray* array);

// print value
void printValue(Value value);
#endif
