#include "heapmgr.h"
#include "data.h"
#include "debug.h"
#include <limits.h>
#include <stdlib.h>
#include <math.h>

// #define mb asm volatile ("mfence":::"memory")

int heapalloc(const int pid, const int size) {
    heap_first->calls++;
    heap_next->calls++;
    heap_best->calls++;
    heap_worst->calls++;

    if (size < HEAP_ALLOC_MIN || size > HEAP_ALLOC_MAX) {
        // Conta como alocação recusada
        heap_first->negated++;
        heap_next->negated++;
        heap_best->negated++;
        heap_worst->negated++;
        return HEAP_ALLOC_OUTOFRANGE;
    }

    clock_t clock_start, clock_end;     // Tempos de início e de fim da alocação
    int crossed;
    int success = 0;                    // Quais algoritmos conseguiram alocar

    /* First-fit */
    clock_start = clock();
    if ((crossed = heapalloc_first(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_first->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_first->crossed += crossed;
        success += HEAP_ALG_FIRST;
    } else {
        heap_first->negated++;
    }

    /* Next-fit */
    clock_start = clock();
    if ((crossed = heapalloc_next(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_next->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_next->crossed += crossed;
        success += HEAP_ALG_NEXT;
    } else {
        heap_next->negated++;
    }

    /* Best-fit */
    clock_start = clock();
    if ((crossed = heapalloc_best(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_best->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_best->crossed += crossed;
        success += HEAP_ALG_BEST;
    } else {
        heap_best->negated++;
    }

    /* Worst-fit */
    clock_start = clock();
    if ((crossed = heapalloc_worst(pid, size)) != HEAP_ALLOC_NOAVAIL) {
        clock_end = clock();
        heap_worst->time += (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
        heap_worst->crossed += crossed;
        success += HEAP_ALG_WORST;
    } else {
        heap_worst->negated++;
    }

    return success;
}

int heapfree(const int pid) {
    for (int i = 0; i < heap_first->capacity; i++) {
        if (heap_first->pid[i] == pid)
            heap_first->pid[i] = PID_NULL;
    }

    for (int i = 0; i < heap_next->capacity; i++) {
        if (heap_next->pid[i] == pid)
            heap_next->pid[i] = PID_NULL;
    }

    for (int i = 0; i < heap_best->capacity; i++) {
        if (heap_best->pid[i] == pid)
            heap_best->pid[i] = PID_NULL;
    }

    for (int i = 0; i < heap_worst->capacity; i++) {
        if (heap_worst->pid[i] == pid)
            heap_worst->pid[i] = PID_NULL;
    }

    return HEAP_FREE_SUCCESS;
}

int heapfragcount(HEAP *heap) {
    int free  = 0;
    int frag  = 0;

    for (int i = 0; i < heap->capacity; i++) {
        if (heap->pid[i] == PID_NULL) {
            free++;
            if (i == heap->capacity - 1 && (free == 1 || free == 2)) {
                frag++;
            }
        } else {
            if (free == 1 || free == 2) {
                frag++;
            }
            free = 0;
        }
    }

    return frag;
}

int heapleakcount(HEAP *heap) {
    /* Assumimos que a aplicação chegou ao fim. */
    int count = 0;
    for (int i = 0; i < heap->capacity; i++) {
        if (heap->pid[i] != PID_NULL)
            count++;
    }
    return count;
}

int heapalloc_first(const int pid, const int size) {
    int free      = 0;
    int init      = 0;
    int available = 0;
    int crossed   = 0;

    for (int i = 0; i < heap_first->capacity; i++) {
        crossed++;
        if (heap_first->pid[i] == PID_NULL) {
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
        for (int i = init; i < init + size; i++)
            heap_first->pid[i] = pid;
        heap_first->top = init + size;
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
        if (heap_next->pid[i] == PID_NULL)
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
        for (int i = init; i < init + size; i++)
            heap_next->pid[i] = pid;
        heap_next->top = init + size; // devolve os blocos que percorreu
        return crossed;
    }
    else
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
        if (heap_best->pid[i] == PID_NULL) {
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
        for (int i = init; i < init + size; i++) {
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
        if (heap_worst->pid[i] == PID_NULL) {
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
        for (int i = init; i < init + size; i++) {
            heap_worst->pid[i] = pid;
        }
        heap_worst->top = init + size;
    } else
        return HEAP_ALLOC_NOAVAIL;

    return crossed;
}


void heaprequest_start(unsigned int seed) {
    /* Método: aleatoriedade */
    srand(seed);
}

#define M_PI acos(-1.0)

int heaprequest(void) {
    double x = (rand() % 6284) / 1000.;                     // Gera [0 .. 2×pi]
    int p = (int) ((sin(x - M_PI / 2.) + 1.) / 2. * 100.);  // Gera [0 .. 100]
    int r = rand() % 101;                                   // Gera [0 .. 100]
    debug("x = %.3lf; p = %3d; r = %3d => [%s]\n", x, p, r, (p - r >= 0) ? "ACCEPTED" : "REJECTED");
    return (p - r >= 0);
}

int heaprequest_size(void) {
    return (rand() % (HEAP_ALLOC_MAX - HEAP_ALLOC_MIN + 1) + HEAP_ALLOC_MIN);
}