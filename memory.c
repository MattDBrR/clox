#include <stdlib.h>

#include "memory.h"

// Wrapper around the realloc function defined in <stdlib.h>
// Only function to dynamic manage the memory
void* reallocate(void* pointer, size_t oldSize, size_t newSize){
    // free
    if (newSize == 0){
        free(pointer);
        return NULL;
    }
    // if pointer = null & oldSize = 0, calling realloc equ to malloc
    void* result = realloc(pointer, newSize);
    // if malloc fail
    if (result == NULL) exit(1);
    return result;
}
