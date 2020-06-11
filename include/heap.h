#ifndef HEAP_H
#define HEAP_H

typedef struct block
{
    void *data; // apontador!
    struct block *next;
} BLOCK;

typedef struct heap
{
    int capacity;
    BLOCK *blocks;
} HEAP;

#define HEAP_CAPACITY 256
#define BLOCK_SIZE 2048

HEAP *makeheap(const int);
BLOCK *makeblock(void);
BLOCK *appendblock(BLOCK *, BLOCK *);
void freeheap(HEAP *);

#endif