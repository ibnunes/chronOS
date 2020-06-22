#ifndef HEAPMGR_H
#define HEAPMGR_H

#include "types.h"

int heapalloc(const int pid, const int size);
int heapfree(const int pid);
int heapfragcount(HEAP *heap);
int heapleakcount(HEAP *heap);

int heapalloc_first(const int pid, const int size);
int heapalloc_next(const int pid, const int size);
int heapalloc_best(const int pid, const int size);
int heapalloc_worst(const int pid, const int size);

/* Solicitação de alocação */
void heaprequest_start(unsigned int seed);
int heaprequest(void);
int heaprequest_size(void);

int heapfree_exclusive(const int pid, const int many);
void heaprequest_exclusive(void);

#endif