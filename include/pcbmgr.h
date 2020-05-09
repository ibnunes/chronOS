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

/* Struct:  PCB
 * ------------
 * Represents Process Control Block.
 * TODO!
 * 
 * 
 */
typedef struct{
    char name;
    int  start;
    process * p;
} PCB;


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

#endif