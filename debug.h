#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"


// name to tell which chunk we are looking at
//
void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);
#endif
