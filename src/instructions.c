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
//    instructions.c, related to processor.h
//
// DESCRIPTION:
// -----------
// Process management: instructions.
//------------------------------------------------------------------------------

#include "processor.h"
#include "pcbmgr.h"

void changeValue(process *p, int n) {
    p->context = n;
}

void addValue(process *p, int n) {
    p->context += n;
}

void subtractValue(process *p, int n) {
    p->context -= n;
}

void blockProcess(process *p) {
    p->state = switchState(p->state, STATUS_BLOCKED);
}

void terminateProcess(process *p) {
    p->state = switchState(p->state, STATUS_TERMINATED);
}

void forkProcess(MEMORY *mem, process *p) {
    instruction *inst = &(mem->cells[p->counter]);
    size_t size = p->instsize - p->counter;
    int address = memalloc(mem, inst, size);
    if (address != MEMERR_ALLOC_NOAVAIL)
        processalloc(pcb, p->pid, inst->name, address, size);
}

void cleanProgram(MEMORY *mem, process *p, char *filename) {
    // memfree(mem, p->counter, p->instsize - p->counter);
    memfree(mem, p->start, p->instsize);
    size_t n;
    instruction *inst = program_read_from_file(filename, &n);
    int address = memalloc(mem, inst, n);
    long index = pcb_index_of_pid(p->pid, pcb);
    pcb->proc[index].start    = address;
    pcb->proc[index].counter  = address;
    pcb->proc[index].instsize = n;
    strcpy(pcb->proc[index].name, filename);
}
