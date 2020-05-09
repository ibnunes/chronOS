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

/* Struct: process
 * ---------------
 * Represents a process.
 * 
 *  int id: identifies the process with a unique integer value.
 *  int context: represents the mutable value which will be altered by the processor.
 *  int * counter: points towards the current instruction that process is at.
 *  int pid: identifies the parent process.
 *  int priority: defines the priority of execution of the process.
 *  int time_limit: 
 *  char state: defines which state of execution the process is at.
 */
typedef struct {
    int  id;         // identificador do processo
    int  context;    // estado do processo
    int * counter;    // contador do programa
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

/* Function: processorFunction
 * ---------------------------
 * Executes an instruction to the corresponding process.
 * 
 *  i: pointer to the instruction to be executed.
 *  p: pointer to the process that will be modified.
 * 
 *  returns: void
 */
void processorFunction(instruction* i, process* p);

/* Function: changeValue
 * ---------------------
 * Defines n as the context of a process.
 * 
 *  p: pointer to the process that will be modified.
 *  n: value to be defined as the context of the process.
 * 
 *  returns: void
 */
void changeValue(process* p, int n);

/* Function: addValue
 * ------------------
 * Adds n to the context of a process.
 * 
 *  p: pointer to the process that will be modified.
 *  n: value to be added to the context of the process.
 * 
 *  returns: void
 */
void addValue(process* p, int n);

/* Function: subtractValue
 * -----------------------
 * Subtracts n to the context of a process.
 * 
 *  p: pointer to the process that will be modified.
 *  n: value to be subtracted to the context of the process.
 * 
 *  returns: void
 */
void subtractValue(process* p, int n);

/* Function: blockProcess
 * ----------------------
 * Changes the state of a process to 'B'(Blocked).
 * 
 *  p: pointer to the process that will be modified.
 * 
 *  returns: void
 */
void blockProcess(process* p);

/* Function: terminateProcess
 * --------------------------
 * Changes the state of a process to 'T'(Terminated).
 * 
 * p: pointer to the process that will be modified.
 * 
 * returns: void
 */
void terminateProcess(process* p);

/* Function: createNewProcess
 * --------------------------
 * Creates a new process based on the process p and moves n-1 lines to the 
 * end of the memory array.
 * 
 *  p: pointer to the process that will be modified.
 *  n: number of lines to skip in the memory.
 * 
 *  returns: void.
 */
void createNewProcess(process* p, int n);


/* Function: cleanProgram
 * ----------------------
 * Clears all following instructions associated with the current process 
 * in the memory array and loads the file filename into the memory.
 * 
 *  filename: string with the name of the file from where the new instructions
 *  will be loaded.
 * 
 *  returns: void
 */
void cleanProgram(char* filename);

#endif
