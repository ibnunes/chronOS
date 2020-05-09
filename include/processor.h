#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memmgr.h"

typedef struct {
    int  id;         // identificador do processo
    int  context;    // estado do processo
    int  counter;    // contador do programa
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

void processorFunction(instruction*, process*);

void changeValue(process*, int);
void addValue(process*, int);
void subtractValue(process*, int);
void blockProcess(process*);
void terminateProcess(process*);
void createNewProcess(process*, int);
void cleanProgram(char*);

#endif
