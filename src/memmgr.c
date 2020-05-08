#include "memmgr.h"


instruction *memalloc(size_t nmemb) {
    instruction *mem = malloc(nmemb * sizeof(instruction));
    for (size_t i = 0; i < nmemb; i++) {
        mem[i].ins  = '\0';
        mem[i].n    = 0;
        // strcpy(mem[i].name, NULL);
    }
    return mem;
}


void memfree(instruction *mem) {
    free(mem);
}
