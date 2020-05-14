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
//    pcbmgr.h
//
// DESCRIPTION:
// -----------
// Process Control Block management.
//------------------------------------------------------------------------------


#ifndef PCBMGR_H
#define PCBMGR_H

#include <stdlib.h>
#include "types.h"


/* Function:  pcballoc
 * -------------------
 * Allocates a PCB table with given number of members.
 * 
 *  nmemb: the number of lines the table must contain.
 * 
 *  returns: pointer to the array representing the PCB table.
 */
PCB *pcballoc(size_t nmemb);

/* Function:  pcbfree
 * ------------------
 * Frees all resources associated with a PCB table.
 * 
 *  pcb: the PCB table.
 * 
 *  returns: nothing.
 */
void pcbfree(PCB *pcb);

/* Function:  maxpid
 * -----------------
 * Determines which is the current maximum PID on the PCB table.
 * 
 *  pcb: the PCB table where to search.
 * 
 *  returns: the maximum PID of all.
 */
int maxpid(PCB *pcb);

/* Function:  processalloc
 * -----------------------
 * Allocates a new process in the PCB table wherever space is available.
 * Should only be called if memory was successfully allocated!
 * 
 *  pcb: PCB table where to allocate to.
 *  ppid: PID of the parent process.
 *  name: name of this new process.
 *  memlocal: start of instructions in memory.
 *  instsize: size of instructions in memory.
 * 
 *  returns: index on the PCB table, or -2 if no space is available.
 */
int processalloc(PCB *pcb, int ppid, char* name, size_t memlocal, size_t instsize);

/* Function:  getPCBIndex
 * ----------------------
 * Returns the index value of where a process is stored in the PCB table based on it's PID.
 * 
 *  PID: the PID to search for.
 *  pcb: the PCB table.
 *  
 *  returns: index to the position of the process in the PCB table, or -1 if non-existent
 */
long pcb_index_of_pid(int PID, PCB *pcb);


#endif