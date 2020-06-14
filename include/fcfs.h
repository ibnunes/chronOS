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
//    fcfs.h
//
// DESCRIPTION:
// -----------
// First Come First Serve algorithm.
//------------------------------------------------------------------------------

#ifndef FCFS_H
#define FCFS_H

#include "types.h"

#define FCFS_END -1

/* Function:  fcfs
 * ---------------
 * Executes the processes in the PCB table using the FCFS algorithm.
 * 
 *  pcb: the PCB table with the processes.
 *  mem: the memory array.
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: next PCB index, or FCFS_END if ended.
 */
int fcfs(PCB *pcb, MEMORY *mem, int pcbindex);

/* Funtion: findsj
 * ---------------
 * Searches pcb table for process with shortest timelimit(burst time).
 * 
 *  pcb: the PCB table with the processes.
 * 
 *  return: PCB table index of process with shorstest timelimit.
 */
int findsj(PCB *pcb);

/* Function: sjf
 * ------------
 * Executes the process in the PCB table using the SJF algorithm.
 * 
 *  pcb: the PCB table with the processes;
 *  mem: the memory array;
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: return: next PCB index, or FCFS_END if ended.
 */
int sjf(PCB *pcb, MEMORY *mem, int pcbindex);

/* Function: rrobin
 * ----------------
 * Executes the process in the PCB table using the Round Robin algorithm.
 *  
 *  pcb: the PCB table with the processes;
 *  mem: the memory array;
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: return: next PCB index, or FCFS_END if ended.
 */
int rrobin(PCB *pcb, MEMORY *mem, int pcbindex);
#endif