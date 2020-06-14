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

#define FCFS 1
#define SJF 2
#define RR 3

#define SCHEDUALING_COUNTER 4 //Number of instructions to be executed in a row before moving to next process

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
 *  return: next PCB index, or FCFS_END if ended.
 */
int sjf(PCB *pcb, MEMORY *mem, int pcbindex);

/* Function: checkPCBStatus
 * ------------------------
 * Checks if there is any process left to run through the processor.
 * 
 *  pcb: the PCB table with the processes;
 *  
 *  return: 1 if true, 0 if false.
 */
int checkPCBStatus(PCB *pcb);

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