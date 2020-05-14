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

#include "types.h"
#include "data.h"
#include "memmgr.h"


/* Function: run
 * -------------
 * Executes the next instruction of a process.
 *
 *  mem: pointer to the memory array.
 *  p: pointer to the process that will be executed and/or modified.
 *
 *  returns: void
 */
void run(MEMORY *mem, process *p);

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
 *
 *  returns: void.
 */
void forkProcess(MEMORY *mem, process *p);


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
void cleanProgram(MEMORY *mem, process *p, char *filename);


/* Function:  switchState
 * ----------------------
 * Verifies if its possible to switch the change from the old state to
 * the new state.
 *
 *  oldstate: integer with the old respective STATUS
 *  newstate: integer with the new respective STATUS
 *
 *  returns: integer
 */
int switchState(int oldstate, int newstate);

#endif
