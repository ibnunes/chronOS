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

void forkProcess(MEMORY *mem, process *p) {
    instruction *inst = &(mem->cells[p->counter]);
    size_t size = p->instsize - p->counter;
    int address = memalloc(mem, inst, size);
    if (address != MEMERR_ALLOC_NOAVAIL) {
        processalloc(pcb, p->pid, inst->name, address, size);
    }
}

void cleanProgram(MEMORY *mem, process *p, char *filename) {
    memfree(mem, p->counter, p->instsize - p->counter);
    size_t n;
    instruction *inst = program_read_from_file(filename, &n);
    int address = memalloc(mem, inst, n);
    long index = pcb_index_of_pid(p->pid, pcb);
    pcb->proc[index].start    = address;
    pcb->proc[index].instsize = n;
    strcpy(pcb->proc[index].name, filename);
}
