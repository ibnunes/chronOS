#include "heapmgr.h"
#include "data.h"
#include <limits.h>

int heapalloc(const int pid, const int size) {
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
    for (int i = 0; i < heap_first->capacity; i++) {
        if (heap_first->pid[i] == pid)
            heap_first->pid[i] = 0;
    }

    for (int i = 0; i < heap_next->capacity; i++) {
        if (heap_next->pid[i] == pid)
            heap_next->pid[i] = 0;
    }

    for (int i = 0; i < heap_best->capacity; i++) {
        if (heap_best->pid[i] == pid)
            heap_best->pid[i] = 0;
    }

    for (int i = 0; i < heap_worst->capacity; i++) {
        if (heap_worst->pid[i] == pid)
            heap_worst->pid[i] = 0;
    }

    return HEAP_FREE_SUCCESS;
}

int heapfragcount(HEAP* heap) {
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
    int init      = 0;          // Bloco a partir do qual se irá alocar memória
    int curr      = 0;          // Bloco actual a ser considerado para alocação
    int min       = INT_MAX;    // Menor tamanho disponível tal que seja pelo menos size
    int free      = 0;          // Blocos livres contíguos
    int crossed   = 0;          // Blocos percorridos na pesquisa
    int available = 0;          // Existe memória disponível para alocar?
    int hasmem    = 0;          // O bloco curr tem size blocos após si disponíveis?

    for (int i = 0; i < heap_best->capacity; i++) {
        crossed++;
        if (heap_best->pid[i] == 0) {
            if (free == 0) curr = i;
            free++;
            if (free == size) {
                available = 1;
                hasmem    = 1;
            }
            if ((i == heap_best->capacity - 1) && hasmem && (free < min)) {
                min  = free;
                init = curr;
            }
        } else {
            if (hasmem) {
                if (free < min) {
                    min  = free;
                    init = curr;
                }
                hasmem = 0;
            }
            free = 0;
        }
    }

    if (available) {
        for (int i = init; i < size; i++) {
            heap_best->pid[i] = pid;
        }
        heap_best->top = init + size;
    } else
        return HEAP_ALLOC_NOAVAIL;

    return crossed;
}

int heapalloc_worst(const int pid, const int size) {
    int init      = 0;          // Bloco a partir do qual se irá alocar memória
    int curr      = 0;          // Bloco actual a ser considerado para alocação
    int max       = 0;          // Maior tamanho disponível tal que seja pelo menos size
    int free      = 0;          // Blocos livres contíguos
    int crossed   = 0;          // Blocos percorridos na pesquisa
    int available = 0;          // Existe memória disponível para alocar?
    int hasmem    = 0;          // O bloco curr tem size blocos após si disponíveis?

    for (int i = 0; i < heap_worst->capacity; i++) {
        crossed++;
        if (heap_worst->pid[i] == 0) {
            if (free == 0) curr = i;
            free++;
            if (free == size) {
                available = 1;
                hasmem    = 1;
            }
            if ((i == heap_worst->capacity - 1) && hasmem && (free > max)) {
                max  = free;
                init = curr;
            }
        } else {
            if (hasmem) {
                if (free > max) {
                    max  = free;
                    init = curr;
                }
                hasmem = 0;
            }
            free = 0;
        }
    }

    if (available) {
        for (int i = init; i < size; i++) {
            heap_worst->pid[i] = pid;
        }
        heap_worst->top = init + size;
    } else
        return HEAP_ALLOC_NOAVAIL;

    return crossed;
}
