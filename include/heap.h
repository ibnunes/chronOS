#ifndef HEAP_H
#define HEAP_H

#include "types.h"

#define HEAP_CAPACITY 256
#define BLOCK_SIZE 2048

HEAP *makeheap(const int);
BLOCK *makeblock(void);
BLOCK *appendblock(BLOCK *, BLOCK *);
void destroyheap(HEAP *);

#endif