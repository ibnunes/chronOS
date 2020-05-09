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
//    processor.h
//
// DESCRIPTION:
// -----------
// Process management.
//------------------------------------------------------------------------------


#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memmgr.h"

typedef struct {
    int  id;         // identificador do processo
    int  context;    // estado do processo
    int  counter;    // contador do programa
    int  pid;        // identificador do processo progenitor
    int  priority;   // prioridade do processo
    int  time_limit; // prazo temporal do processo
    char state;      // estado bloquado, terminado, ready, etc.
    // add whatever else is needed
} process;

/* 5 states:
 * 'N' -> New
 * 'r' -> Ready
 * 'R' -> Running
 * 'B' -> Blocked
 * 'T' -> Terminated
 */

/* Processes an instruction from a process */
void processorFunction(instruction*, process*);

/* M n: mudar o valor da variável para o valor n. */
void changeValue(process*, int);

/* A n: adicionar o valor n à variável. */
void addValue(process*, int);

/* S n: subtrair o valor n à variável. */
void subtractValue(process*, int);

/* B: bloquear este processo. */
void blockProcess(process*);

/* T: terminar este processo. */
void terminateProcess(process*);

/* C n: criar um novo processo filho, o processo pai executa n linhas à frente. */
process *createNewProcess(process*, int);

/* L: limpar o programa atual e substituir pelo novo. */
void cleanProgram(char*);

#endif