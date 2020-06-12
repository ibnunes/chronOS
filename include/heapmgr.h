#ifndef HEAPMGR_H
#define HEAPMGR_H

#include "types.h"

#define HEAP_ALLOC_MIN 3        // Mínimo de 3 partições alocadas
#define HEAP_ALLOC_MAX 10       // Máximo de 10 partições alocadas

#define HEAP_ALLOC_NOAVAIL -1   // Erro: não há memória heap disponível
#define HEAP_FREE_SUCCESS   1   // Sucesso: memória heap libertada
#define HEAP_FREE_FAILURE  -1   // Erro: a memória heap não pôde ser libertada

#define HEAP_ALG_FIRST 1        // Algoritmo de alocação: First-fit
#define HEAP_ALG_NEXT  2        // Algoritmo de alocação: Next-fit
#define HEAP_ALG_BEST  4        // Algoritmo de alocação: Best-fit
#define HEAP_ALG_WORST 8        // Algoritmo de alocação: Worst-fit

int heapalloc(const int pid, const int size);
int heapfree(const int pid);
int heapfragcount(HEAP* heap);

int heapalloc_first(const int pid, const int size);
int heapalloc_next(const int pid, const int size);
int heapalloc_best(const int pid, const int size);
int heapalloc_worst(const int pid, const int size);

#endif