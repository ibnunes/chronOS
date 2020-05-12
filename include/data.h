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
//    types.h
//
// DESCRIPTION:
// -----------
// Global variables for the whole program.
//------------------------------------------------------------------------------


#ifndef DATA_H
#define DATA_H

#include "types.h"
#include <time.h>

MEMORY  *memory;         // Memória
PCB     *pcb;            // Tabela PCB (Process Control Block)
clock_t cputime;         // Tempo atual do processador
plan_q  *plan;           // Plano: lista de processos e tempos de entrada


#endif