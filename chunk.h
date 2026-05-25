#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// VM instructions
typedef enum{
    OP_CONSTANT,
    OP_NEGATE,
    OP_RETURN,
    OP_ADD, // Binary op
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
} OpCode;

// Simply a wrapper around a dynamic array of bytes.
typedef struct{
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

// Constructor for Chunk.
void initChunk(Chunk* chunk);
// Write instruction
void writeChunk(Chunk* chunk, uint8_t byte, int line);
// Add constant to the chunk
int addConstant(Chunk* chunk, Value value);
// Destructor of Chunk
void freeChunk(Chunk* chunk);
#endif
