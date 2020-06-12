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


#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "memmgr.h"
#include "pcbmgr.h"
#include "processor.h"
#include "plan.h"
#include "debug.h"
#include "fcfs.h"

#include "heap.h"

// #include "data.h"
// #include "types.h"

#define DEFAULT_TIME_QUANTUM 0.500F         // 500 milissegundos
#define PID_MANAGER 0                       // PID do processo gestor

/* Function:  create_new_process
 * -----------------------------
 * Creates a new process in memory and in the PCB table.
 * 
 *  pcb: the PCB table.
 *  fname: file name of the program.
 * 
 *  return: 1 if success, error code <= 0 if otherwise.
 */
int create_new_process(PCB *pcb, char *fname);

#endif