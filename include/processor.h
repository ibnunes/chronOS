#include "simulator.h"

<<<<<<< HEAD:processor.h
void changeValue (process * p, int n);
=======

typedef struct{
    int id;         // identificador do processo
    int state;      // estado do processo
    int counter;    // contador do programa
    int pid;        // identificador do processo progenitor
    int priority;   // prioridade do processo
    int time_limit; // prazo temporal do processo
    instruction instructionList;
    // add whatever else is needed
} process;

void changeValue(process * p, int n);
>>>>>>> bbfe6398c26265dfe219d6726f391520d7567c48:include/processor.h

void addValue(process * p, int n);

void subtractValue(process * p, int n);

void blockProcess(process * p);

void terminateProcess(process * p);

process *createNewProcess(process * p, int n);

void cleanProgram(char * filename);
