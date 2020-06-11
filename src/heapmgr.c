#include "heapmgr.h"

int heapalloc(const int pid, const int size, const int __algorithm) {
    switch (__algorithm) {
        case HEAP_ALG_FIRST:
            return heapalloc_first(pid, size);
        
        case HEAP_ALG_BEST:
            return heapalloc_best(pid, size);
        
        case HEAP_ALG_WORST:
            return heapalloc_worst(pid, size);
        
        default:
            /* Algoritmo por defeito:
             * First-fit uma vez que é o mais eficiente.
             */
            return heapalloc_first(pid, size);
    }
}

int heapfree(const int pid) {
    // TODO
    return HEAP_FREE_FAILURE;
}

int heapfragcount(void) {
    // TODO
    return 0;
}

int heapalloc_first(const int pid, const int size) {
    // TODO
    return HEAP_ALLOC_NOAVAIL;
}

int heapalloc_best(const int pid, const int size) {
    // TODO
    return HEAP_ALLOC_NOAVAIL;
}

int heapalloc_worst(const int pid, const int size) {
    // TODO
    return HEAP_ALLOC_NOAVAIL;
}
