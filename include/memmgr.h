#ifndef MEMMGR_H
#define MEMMGR_H

#include <stdlib.h>
// #include <string.h>

#define MAX_NAME 15

typedef struct {
    char ins;               // Instrução
    int  n;                 // Incremento ou decremento da variável
    char name[MAX_NAME];    // Nome do processo filho
} instruction;

typedef struct {
    instruction *cells;     // Células de memória
    size_t capacity;        // Capacidade total de memória
    size_t curr;            // Posição actual para alocar novas instruções (?? a rever com algoritmos de gestão de memória ??)
    size_t free;            // Capacidade livre de memória
} MEMORY;


instruction *memalloc(size_t nmemb);
void memfree(instruction *mem);

#endif