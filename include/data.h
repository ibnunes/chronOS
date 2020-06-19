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
//    data.h
//
// DESCRIPTION:
// -----------
// Global variables for the whole program.
//------------------------------------------------------------------------------


#ifndef DATA_H
#define DATA_H

#include "types.h"
#include <time.h>

MEMORY    *memory;          // Memória
HEAP      *heap_first;      // Memória heap - componente para first-fit
HEAP      *heap_next;       // Memória heap - componente para next-fit
HEAP      *heap_best;       // Memória heap - componente para best-fit
HEAP      *heap_worst;      // Memória heap - componente para worst-fit
PCB       *pcb;             // Tabela PCB (Process Control Block)
clock_t   cputime;          // Tempo atual do processador em milissegundos
plan_q    *plan;            // Plano: lista de processos e tempos de entrada
control_q *control;         // Controlo: lista de instruções de controlo

struct world w;

#endif