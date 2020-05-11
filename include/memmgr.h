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
//    memmgr.h
//
// DESCRIPTION:
// -----------
// Memory management.
//------------------------------------------------------------------------------


#ifndef MEMMGR_H
#define MEMMGR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/*
 * Function:  cleaninstruction
 * ---------------------------
 * Cleans an instruction, storing INSTRUCTION_VOID as the instruction
 * and 0 (zero) as the variable increment.
 *
 *  instruct: pointer to the instruction.
 *
 *  returns: nothing.
 */
void cleaninstruction(instruction *instruct);

/* Function:  memcreate
 * --------------------
 * Creates a memory structure with nmemb cells. It is stored at heap memory.
 * Use memdestroy() to free all the resources.
 * 
 *  nmemb: number of memory cells to allocate.
 * 
 *  returns: a pointer to a MEMORY structure with nmemb cells.
 */
MEMORY *memcreate(size_t nmemb);

/* Function:  memdestroy
 * ---------------------
 * Frees all allocated recources to the memory structure, including the cells.
 * 
 *  memory: pointer to the memory structure to be freed.
 * 
 *  returns: nothing.
 */
void memdestroy(MEMORY *memory);

/* Function:  memalloc
 * -------------------
 * Allocates memory into a memory structure using the fisrt-fit algorithm
 * and stores a given list of instructions.
 * It may generate fragmentation.
 * 
 *  mem: the memory structure where to store the instructions to.
 *  ins: the list of instructions to be stored.
 *  size: the length of the list of instructions.
 * 
 *  returns: index of cell containing the first instruction, or -1 if no
 *  memory is available.
 */
int memalloc(MEMORY* mem, instruction* ins, size_t size);

/* Function:  memfree
 * ------------------
 * Applies cleaninstruction() to 'nmemb' cells of 'mem' memory block
 * starting at index 'init'.
 * ATTENTION: no resources are actually freed from the heap memory!
 * 
 *  mem: the memory structure.
 *  init: the index of the initial cell.
 *  nmemb: the number of cells to be cleaned.
 * 
 *  returns: nothing.
 */
void memfree(MEMORY *mem, size_t init, size_t nmemb);

/* Function: memProgFree
 * ---------------------
 * Cleans and moves all memory cells from start to end to end of memory.
 * 
 *  mem: the memory structure.
 *  start: value of the index at which to start.
 *  end: value of the index at which to end.
 * 
 *  Returns: void.
 */
void memProgFree(MEMORY *mem, int start, int end);

/* Function:  program_read_from_file
 * ---------------------------------
 * Loads instructions from a file into heap memory.
 * They may be allocated later with memalloc() to a memory structure.
 * 
 *  fname: the file name where to read from, including extension.
 *  n: pointer to an integer which will store how many instructions were read.
 * 
 *  returns: pointer to an array of 'n' instructions.
 */
instruction* program_read_from_file(char *fname, size_t *n);

#endif