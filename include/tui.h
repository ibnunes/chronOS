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
//    tui.h
//
// DESCRIPTION:
// -----------
// Text user interface.
//------------------------------------------------------------------------------


#ifndef TUI_H
#define TUI_H

#include "types.h"
#include "data.h"

/* Function:  state2str
 * --------------------
 * Converts a process state to a human readable string format.
 * 
 *  state: the process state.
 * 
 *  returns: a human readable string.
 */
const char *state2str(int state);

/* Function:  pcbreport
 * --------------------
 * Prints a report in the form of a table.
 * 
 *  pcb: the PCB table.
 * 
 *  returns: nothing.
 */
void pcbreport(PCB *pcb);

#endif