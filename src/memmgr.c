#include "memmgr.h"


MEMORY *memalloc(size_t nmemb) {
    MEMORY *memory = malloc(sizeof(MEMORY));
    memory->cells = malloc(nmemb * sizeof(instruction));
    for (size_t i = 0; i < nmemb; i++) {
        memory->cells[i].ins = '\0';
        memory->cells[i].n   = 0;
    }
    return memory;
}


void memfree(MEMORY *memory) {
    free(memory->cells);
    free(memory);
}
