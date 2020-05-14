#include "processor.h"
#include "pcbmgr.h"

// file to do the 7 types of intructions

/* TODO: Write function to add a process to the pcb.
 *       Write function to copy n amount of intructions from the one place in the memory to another.
 *       Write memRemoveInstructions in memmrg.c
 */

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
    // maybe send it's instructions to the end of memory
}

void terminateProcess(process * p) {
    p->state = 'T';
}

void createNewProcess(process * p) {
    process *new_p    = malloc(sizeof(process));
    strcpy(new_p->name, p->name);
    new_p->start      = -1; //
    new_p->id         = p->id+1; //find better scheme to number child processes
    new_p->context    = 0;
    new_p->counter    = p->counter;
    new_p->pid        = p->id;
    new_p->priority   = p->priority;
    new_p->time_limit = p->time_limit;
    new_p->state      = STATUS_NEW;
    new_p->insNum     = p->insNum - p-> counter;

    //add new_p to the pcb
    //copy remaining instructions from parerent into memory
}

void cleanProgram(process * p, char * filename) {
    size_t *n;
    // vvv not implemented yet vvv
    memRemoveInstructions(pcb, p->counter, p->insNum - p->counter);
    strcpy(p->name, filename);
    instruction *ins = program_read_from_file(p->name, n);
    p->insNum = *n;
    memalloc(mem, ins,(size_t)*n);
}
