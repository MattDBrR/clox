// Opcode

#include "stdlib.h"

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_RETURN
};

typedef double Value;

typedef struct{
    int capacity;
    int count;
    Value *values;
} ValueArray;

// Dynamic array
//
typedef struct {
    int capacity;
    int count;
    uint8_t* code;
    // more tracking
    int* lines;
    ValueArray constants; 
} Chunk;

// Method for the chunk

// CHUNK is a sequence of byte and each byte is an opcode
// that refers to an operation
// Basic function to manipulate the chunk
// Since we are going to define multiple dynamic array we define the following macro
// The  three arrays: bytes of code, constant values, and line information for debugging.
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
(type*)reallocate(pointer,sizeof(type)*(oldCount),\
    sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount)\
reallocate(pointer, sizeof(type)* oldCount,0)



