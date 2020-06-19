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
#include "debug.h"

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
    if (p->state == STATUS_TERMINATED)
        p->timeend = cputime;
}

void forkProcess(MEMORY *mem, process *p) {
    instruction *inst = &(mem->cells[p->counter + 1]);
    size_t size = p->instsize - (p->counter + 1 - p->start);
    int address = memalloc(mem, inst, size);
    int pid = PID_NULL;
    if (address != MEMERR_ALLOC_NOAVAIL)
        pid = processalloc(pcb, p->pid, inst->name, address, size, p->priority);
    debug("FORKED %ld instructions from PID %d to address %d with new PID %d.\n", size, p->pid, address, pid);
    write("FORKED %ld instructions from PID %d to address %d with new PID %d.\n", size, p->pid, address, pid);
}

void cleanProgram(MEMORY *mem, process *p, char *filename) {
    char fname[MAX_NAME];
    strcpy(fname, filename);
    memfree(mem, p->start, p->instsize);
    size_t n;
    instruction *inst = program_read_from_file(fname, &n);
    int address = memalloc(mem, inst, n);
    p->start    = address;
    p->counter  = address;
    p->instsize = n;
    strcpy(p->name, fname);
    free(inst);
    debug("CLEANED, then allocated %ld instructions at address %d.\n", n, address);
    write("CLEANED, then allocated %ld instructions at address %d.\n", n, address);
}
