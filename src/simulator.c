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
//    simulator.h
//
// DESCRIPTION:
// -----------
// Simulation management.
// The main header file that aggregates everything.
//------------------------------------------------------------------------------

#include "simulator.h"
#include "data.h"

int create_new_process(PCB *pcb, char *fname) {
    size_t n;
    
    // Ler instruções do ficheiro
    instruction *i = program_read_from_file(fname, &n);

    // Alocar as instruções em memória e obter o endereço (índice) em memória
    int address = memalloc(memory, i, n);
    if (address == MEMERR_ALLOC_NOAVAIL)
        return MEMERR_ALLOC_NOAVAIL;        // Erro: não há memória disponível
    
    int pid = processalloc(pcb, PID_MANAGER, fname, address, n); 

    free(i);        // Libertar os recursos previamente alocados
    debug("%ld instructions from %s allocated to address %d with PID %d.\n", n, fname, address, pid);
    return 1;
}



