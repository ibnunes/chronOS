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
#include "control.h"
#include "debug.h"
#include "scheduling.h"

#include "heap.h"

#include "types.h"

/* Function:  create_new_process
 * -----------------------------
 * Creates a new process in memory and in the PCB table.
 * 
 *  pcb: the PCB table.
 *  fname: file name of the program.
 * 
 *  return: 1 if success, error code <= 0 if otherwise.
 */
int create_new_process(PCB *pcb, PLAN plan);

#endif