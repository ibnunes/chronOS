#ifndef MEMMGR_H
#define MEMMGR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 15             // Nº máximo de caracteres de um programa
#define MAX_INSTRUCTION 30      // Nº máximo de caracteres de uma instrução num ficheiro
#define INSTRUCTION_VOID '\0'   // Instrução void: indica célula de memória livre
#define MEMERR_ALLOC_NOAVAIL -1 // Erro: não há memória imediatamente disponível


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

void cleaninstruction(instruction*);

MEMORY *memcreate(size_t);
void memdestroy(MEMORY*);

int memalloc(MEMORY*, instruction*, size_t);
void memfree(MEMORY*, size_t, size_t);

instruction* program_read_from_file(char*, size_t*);

#endif