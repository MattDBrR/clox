// IMPLEMENTATION OF THE VM

#include <stdint.h>

#define STACK_MAX 256

typedef struct {
    Chunk* chunk; // current chunk
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop; // Point after the last element in the array
} VM;

VM vm; // Global instance that we will use
       //
       
// Method for the stack

void resetStack(){
    vm.stacktop = vm.stack
}

void pushStack(Value value){
    *vm.stackTop = value;
    stackTop++;
}


