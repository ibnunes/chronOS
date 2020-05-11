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

/* Function: getPCBIndex
 * ---------------------
 * Returns the index value of where a process is stored in the PCB table based on it's PID.
 * 
 *  pcb: the PCB table.
 *  
 *  returns: index to the position of the process in the PCB table
 */
int getPCBIndex(PCB *pcb, int PID);

/* Functin: pcbCellFree
 * --------------------
 * Frees a single array cell in the PCB table.
 * 
 * pdb: the PCB table.
 * pid: process id to the PCB cell to be removed from the PCB table.
 * 
 * returns: int value for the index of the start of the following process in memory.
 */
int pcbCellFree(PCB *pcb, int PID);

#endif