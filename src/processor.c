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
//    processor.h
//
// DESCRIPTION:
// -----------
// Process management.
//------------------------------------------------------------------------------


#include "processor.h"
#include "debug.h"

void run(MEMORY *mem, process *p) {
    if ((size_t) p->counter >= p->start + p->instsize) {
        p->state = switchState(p->state, STATUS_TERMINATED);
        return;
    }

    instruction *i = &(mem->cells[p->counter]);

    switch (i->ins) {
        case INSTRUCTION_CHANGE:
            debug("PID %d: instruction \"M %d\"\n", p->pid, i->n);
            changeValue(p, i->n);
            break;

        case INSTRUCTION_ADD:
            debug("PID %d: instruction \"A %d\"\n", p->pid, i->n);
            addValue(p, i->n);
            break;

        case INSTRUCTION_SUBTRACT:
            debug("PID %d: instruction \"S %d\"\n", p->pid, i->n);
            subtractValue(p, i->n);
            break;

        case INSTRUCTION_BLOCK:
            debug("PID %d: instruction \"B\"\n", p->pid);
            blockProcess(p);
            break;

        case INSTRUCTION_TERMINATE:
            debug("PID %d: instruction \"T\"\n", p->pid);
            terminateProcess(p);
            return;

        case INSTRUCTION_FORK:
            debug("PID %d: instruction \"C %d\"\n", p->pid, i->n);
            forkProcess(mem, p);
            p->counter += i->n; // jump n instructions
            return;

        case INSTRUCTION_CLEAR:
            debug("PID %d: instruction \"L %s\"\n", p->pid, i->name);
            cleanProgram(mem, p, i->name);
            return;
        
        case INSTRUCTION_ALLOC:
            debug("PID %d: instruction \"K %d\"\n", p->pid, i->n);
            int alg;
            if ((alg = heapalloc(p->pid, i->n)) == HEAP_ALLOC_OUTOFRANGE) {
                debug("Failed to allocate memory for PID %d\n", p->pid);
                write("Failed to allocate memory for PID %d\n", p->pid);
            } else {
                debug("Allocated %d block of heap memory (return code = %d)\n", i->n, alg);
                write("Allocated %d block of heap memory (return code = %d)\n", i->n, alg);
            }
            break;
        
        case INSTRUCTION_FREE:
            debug("PID %d: instruction \"F\"\n", p->pid);
            if (heapfree(p->pid) == HEAP_FREE_FAILURE) {
                debug("Failed to deallocate heap memory for PID %d\n", p->pid);
                write("Failed to deallocate heap memory for PID %d\n", p->pid);
            } else {
                debug("Deallocated heap memory\n");
                write("Deallocated heap memory\n");
            }
            break;

        default:
            fprintf(stderr, "ERROR: Unknown instruction \"%c\". ABORTING!\n", i->ins);
            exit(-1);
            break;
    }

    p->counter++;
}

int switchState(int oldstate, int newstate) {
    switch (oldstate) {
        case STATUS_NEW:
            return (newstate == STATUS_READY) ? newstate : oldstate;

        case STATUS_READY:
            return (newstate == STATUS_RUNNING) ? newstate : oldstate;

        case STATUS_RUNNING:
            return (
                    newstate == STATUS_TERMINATED ||
                    newstate == STATUS_BLOCKED ||
                    newstate == STATUS_READY
                ) ? newstate : oldstate;

        case STATUS_BLOCKED:
            return (newstate == STATUS_READY) ? newstate : oldstate;

        case STATUS_TERMINATED:
        default:
            return oldstate;
    }
}
