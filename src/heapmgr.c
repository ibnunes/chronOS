#include "heapmgr.h"
#include "data.h"
#include "types.h"

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
    int free      = 0;
    int init      = 0;
    int available = 0;
    int crossed   = 0;


    
    for (int i = 0; i < heap_first->capacity; i++) {
        crossed++;
        if (heap_first->pid[i] == 0) {
            if (free == 0) 
                init = i;
            free++;

            if (free == size) {
                available = 1;
                break;
            }
        }
        else
            free = 0;
    }

    if (available) {
        for (int i = init; i < size; i++)
            heap_first->pid[i] = pid;
        heap_first->top = (init + size);
        return crossed; // devolve os blocos que percorreu
    }
    else
        return HEAP_ALLOC_NOAVAIL;
}

int heapalloc_next(const int pid, const int size) {
    int free      = 0;
    int init      = 0;
    int available = 0;
    int crossed   = 0;

    for (int i = heap_next->top; i < heap_next->capacity; i++)
    {
        crossed++;
        if (heap_next->pid[i] == 0)
        {
            if (free == 0)
                init = i;
            free++;

            if (free == size)
            {
                available = 1;
                break;
            }
        }
        else
            free = 0;
    }

    if (available)
    {
        for (int i = init; i < size; i++)
            heap_next->pid[i] = pid;
        heap_next->top = (init + size); // devolve os blocos que percorreu
        return crossed;
    }
    else
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
