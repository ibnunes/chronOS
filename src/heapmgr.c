#include "heapmgr.h"

int heapalloc(const int pid, const int size, const int __algorithm) {
    clock_t clock_start, clock_end;     // Tempos de início e de fim da alocação
    int crossed;
    int success = 0;                    // Quais algoritmos conseguiram alocar

    /* First-fit */
    clock_start = clock();
    if ((crossed = heapalloc_first(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_first->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_first->calls++;
        heap_first->crossed += crossed;
        success += HEAP_ALG_FIRST;
    }

    /* Next-fit */
    clock_start = clock();
    if ((crossed = heapalloc_next(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_next->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_next->calls++;
        heap_next->crossed += crossed;
        success += HEAP_ALG_NEXT;
    }

    /* Best-fit */
    clock_start = clock();
    if ((crossed = heapalloc_best(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_best->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_best->calls++;
        heap_best->crossed += crossed;
        success += HEAP_ALG_BEST;
    }

    /* Worst-fit */
    clock_start = clock();
    if ((crossed = heapalloc_worst(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_worst->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_worst->calls++;
        heap_worst->crossed += crossed;
        success += HEAP_ALG_WORST;
    }

    return success;
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

int heapalloc_next(const int pid, const int size) {
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
