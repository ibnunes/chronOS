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
//    scheduling.h
//
// DESCRIPTION:
// -----------
// Scheduling algorithms.
//------------------------------------------------------------------------------

#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "types.h"

#define SCHEDULING_COUNTER 5 //Number of instructions to be executed in a row before moving to next process

/* Function:  ltsched
 * ---------------
 * Changes the state of every Blocked process to Ready.
 * 
 *  pcb: the PCB table with the processes.
 * 
 *  return: number of processes changed to Ready.
 */
int ltsched(PCB *pcb);

/* Function:  fcfs
 * ---------------
 * Executes the processes in the PCB table using the FCFS algorithm.
 * 
 *  pcb: the PCB table with the processes.
 *  mem: the memory array.
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: next PCB index, or SCHEDULER_END if ended.
 */
int fcfs(PCB *pcb, MEMORY *mem, int pcbindex);

/* Function:  sortedbt
 * ---------------
 * Verify if the array is actually sorted by burst time.
 * 
 *  p: array of process struct
 *  size: size of the array p
 * 
 *  return: 1 if sorted else 0
 */
int sortedbt(process *p, size_t size);

/* Function:  sortedpri
 * ---------------
 * Verify if the array is actually sorted by priority.
 * 
 *  p: array of process struct
 *  size: size of the array p
 * 
 *  return: 1 if sorted else 0
 */
int sortedpri(process *p, size_t size);

/* Function:  comparebt
 * ---------------
 * Compares the priority of 2 processes. 
 * 
 *  v1: process number 1
 *  v2: process number 2
 * 
 *  return: 
 *      -1 when the bursttime of v1 < bursttime of v2, 
 *       0 when the burstime of v1 and v2 is equal,
 *       1 when the bursttime of v1 > bursttime of v2.
 */
    int comparepri(const void *v1, const void *v2);

/* Function:  comparebt
 * ---------------
 * Compares the burst time of 2 processes. 
 * 
 *  v1: process number 1
 *  v2: process number 2
 * 
 *  return: 
 *      -1 when the bursttime of v1 < bursttime of v2, 
 *       0 when the burstime of v1 and v2 is equal,
 *       1 when the bursttime of v1 > bursttime of v2.
 */
int comparebt(const void *v1, const void *v2);

/* Function: psa
 * ------------
 * Executes the process in the PCB table using the Priority Scheduling Algorithm.
 * 
 *  pcb: the PCB table with the processes;
 *  mem: the memory array;
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: next PCB index, or SCHEDULER_END if ended.
 */
int psa(PCB *pcb, MEMORY *mem, int pcbindex);

/* Function: sjf
 * ------------
 * Executes the process in the PCB table using the SJF algorithm.
 * 
 *  pcb: the PCB table with the processes;
 *  mem: the memory array;
 *  pcbindex: current PCB table index at which the manager is working.
 * 
 *  return: next PCB index, or SCHEDULER_END if ended.
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
 *  return: return: next PCB index, or SCHEDULER_END if ended.
 */
int rrobin(PCB *pcb, MEMORY *mem, int pcbindex);
#endif