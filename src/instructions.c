#include "processor.h"

// file to do the 7 types of intructions

void changeValue (process * p, int n) {
    p->context = n;
}

void addValue(process * p, int n) {
    p->context += n;
}

void subtractValue(process * p, int n) {
    p->context -= n;
}

void blockProcess(process * p) {
    p->state = 'B';
    // find out what to do with a blocked process
    //maybe send it to the end of memory
}

void terminateProcess(process * p) {
    p->state = 'T';
    memProgFree(*memory, p->counter, pcbCellFree(*pcb, p->id));
    //kill process by deleting it of memory and PCB
}

void createNewProcess(process * p, int n) {
    process *new_p    = malloc(sizeof(process));
    new_p->id         = p->id+1; //find better scheme to number child processes
    new_p->context    = 0;
    new_p->counter    = p->counter;
    new_p->pid        = p->id;
    new_p->priority   = p->priority;
    new_p->time_limit = p->time_limit;
    new_p->state      = 'N';
    //add whatever else is added in the data sctructure

    return;
}

void cleanProgram(process * p, char * filename) {
    return; // ???
}
