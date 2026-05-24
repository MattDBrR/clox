First we need to implement Bytecode
Bytecode is one level above machine code, it's simple instruction designed for a virtual machine

We define / implement a chunk here 
Chunk is a sequence of bytecode 
For the implementation of a chunk we use a dynamic array

Recall on dynamic array
struct that define the pointer to the first element
capacity of allocation
count of element allocated

uint8_t* code; define our dynamic byte array
realloc(NULL, newSize) behave exatcly like malloc(newSize)
if oldSize = Non-Zero and newSize = 0 that means we want to free our current allocation


Now we have a little module to create chunk of bytecode
