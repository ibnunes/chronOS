#ifndef HEAP_H
#define HEAP_H

#include "types.h"

#define HEAP_CAPACITY  128      // 128 partições
#define BLOCK_SIZE    2048      // 2KB por partição

HEAP *makeheap(const int);
BLOCK *makeblock(void);
BLOCK *appendblock(BLOCK *, BLOCK *);
void destroyheap(HEAP *);

#endif