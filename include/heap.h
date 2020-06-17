#ifndef HEAP_H
#define HEAP_H

#include "types.h"

HEAP *makeheap(const int);
BLOCK *makeblock(void);
BLOCK *appendblock(BLOCK *, BLOCK *);
void destroyheap(HEAP *);

#endif