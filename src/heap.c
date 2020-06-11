#include "heap.h"
#include <stdlib.h>

// criar memória heap
HEAP *makeheap(const int CAPACITY)
{
    HEAP *h = malloc(sizeof(HEAP));
    h->capacity = CAPACITY;
    h->blocks = NULL;
    for (int i = 0; i < CAPACITY; i++)
    {
        h->blocks = appendblock(h->block, makeblock());
    }
    return h;
}

// criar 2KB de inteiros:
BLOCK *makeblock(void)
{
    BLOCK *n = malloc(sizeof(BLOCK));
    n->data = malloc(BLOCK_SIZE);
    n->next = NULL;
}

// fazer append
BLOCK *appendblock(BLOCK *v, BLOCK *n)
{
    if (v == NULL)
        return n;
    BLOCK *head = v;
    while (v->next != NULL)
        v = v->next;
    v->next = n;
    return head;
}

// libertar recursos
void freeheap(HEAP *h)
{
    BLOCK *aux;
    while (h->blocks != NULL)
    {
        aux = h->blocks;
        h->blocks = h->blocks->next;
        free(aux->data);
        free(aux);
    }
    free(h);
}