#include "processor.h"
#include "pcbmgr.h"

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
    p->state = STATUS_BLOCKED;
    // find out what to do with a blocked process
    // maybe send it to the end of memory
}

void terminateProcess(process * p) {
    p->state = STATUS_TERMINATED;
    // TODO: usar método de switch de estados
}

void forkProcess(process * p) {
    process *new_p    = malloc(sizeof(process));
    
    /* strcpy(new_p->name, p->name);
    new_p->start      = -1; //
    new_p->pid        = p->pid+1; //find better scheme to number child processes
    new_p->context    = 0;
    new_p->counter    = p->counter;
    new_p->ppid       = p->pid;
    new_p->priority   = p->priority;
    new_p->timelimit  = p->timelimit;
    new_p->state      = STATUS_NEW;
    new_p->instsize   = p->instsize - p->counter; */

    // TODO: usar métodos memalloc, memfree e processalloc

    /* memalloc(memory, &instruction[curr], total - curr);
     * processalloc(...);
     */

    //add new_p to the pcb
}

void cleanProgram(process *p, char *filename) {
    // Remove remaning instructions from memory
    // ChangeFileName(pcb, p, filename)
    // Load new file to memory

    /* memfree(memory, index, total - curr);
     * memalloc(memory, &instructions[children], size_children);
     */

    return; 
}
