//------------------------------------------------------------------------------
//
// chronOS - A scheduling simulator
//
//    Copyright (C) 2020 Igor Cordeiro Bordalo Nunes (www.igornunes.com)
//    Copyright (C) 2020 Jorge Miguel Louro Pissarra
//    Copyright (C) 2020 Diogo Castanheira Simões
//    Copyright (C) 2020 Universidade da Beira Interior (www.ubi.pt)
//
// RUNTIME LIBRARIES PACKAGE
//    memmgr.h
//
// DESCRIPTION:
// -----------
// Memory management.
//------------------------------------------------------------------------------


#include "memmgr.h"
#include "debug.h"

void cleaninstruction(instruction *instruct) {
    instruct->ins = INSTRUCTION_VOID;
    instruct->n   = 0;
}

MEMORY *memcreate(size_t nmemb) {
    MEMORY *memory = malloc(sizeof(MEMORY));
    memory->cells = malloc(nmemb * sizeof(instruction));
    for (size_t i = 0; i < nmemb; i++)
        cleaninstruction(&memory->cells[i]);
    return memory;
}

void memdestroy(MEMORY *memory) {
    free(memory->cells);
    free(memory);
}

int memalloc(MEMORY* mem, instruction* ins, size_t size) {
    size_t free = 0;
    size_t init = 0;
    int available = 0;

    /* Implementing first-fit */
    // Encontra o primeiro espaço livre disponível
    for (size_t i = 0; i < mem->capacity; i++) {
        if (mem->cells[i].ins == INSTRUCTION_VOID) {
            if (free == 0) init = i;
            free++;
            if (free == size) {
                available = 1;
                break;
            }
        } else {
            free = 0;
        }
    }

    // Se existir, preenche as células com as instruções
    if (available)
        for (size_t i = init, j = 0; j < size; i++, j++)
            mem->cells[i] = ins[j];
    else
        return MEMERR_ALLOC_NOAVAIL;  // Não existe, devolve erro

    // Devolve o endereço da 1ª instrução
    return init;
}

void memfree(MEMORY *mem, size_t init, size_t nmemb) {
    for (size_t i = init; i < nmemb; i++)
        cleaninstruction(&mem->cells[i]);
}


/* TODO: testing */
instruction* program_read_from_file(char *fname, size_t *n) {
    FILE *f = fopen(fname, "r");
    expects(f != NULL);

    *n = 0;
    instruction *instruct = malloc(sizeof(*instruct));
    instruction aux;
    int read;
    char *line;

    while (!feof(f)) {
        aux.ins  = INSTRUCTION_VOID;
        aux.n    = 0;
        // aux.name = NULL;

        line = fgets(line, MAX_INSTRUCTION, f);
        expects(line != NULL);
        if ((read = sscanf(line, "%c %d", &aux.ins, &aux.n)) == 2) {
            goto push_instruction;

        } else if ((read = sscanf(line, "%c %s", &aux.ins, aux.name)) == 2) {
            goto push_instruction;

        } else if ((read = sscanf(line, "%c ", &aux.ins)) == 1) {

push_instruction:
            debug("Pushing (%c, %d, %s) to instruction array...\n", aux.ins, aux.n, aux.name);
            (*n)++;
            instruct = realloc(instruct, (*n) * sizeof(*instruct));
            instruct[*n-1] = aux;
            continue;

        } else {
            fprintf(stderr, "ERROR: only %d out of 1 or 2 items were corretly read from \"%s\".\n", read, line);
        }
    }

    fclose(f);
    return instruct;
}
